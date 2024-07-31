// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "System/NFGameInstance.h"
#include "Managers/InventoryManager.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	//InventorySize = 100;

	//InitializeInventory();
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(DEBUG_TEXT("Inventory Component BeginPlay()"));

}

void UInventoryComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	////InventorySize의 값이 변경됐을 때 인벤토리의 크기를 다시 재조정한다.
	//FProperty* prop = PropertyChangedEvent.Property;
	//if (prop->GetName() == TEXT("InventorySize"))
	//{
	//	//InitializeInventory();
	//}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InitInventoryComponent()
{
	Debug::Print(DEBUG_TEXT("Inventory Component Init()"));

	auto inventoryManager = UNFGameInstance::GetInventoryManager();

	if (IsValid(inventoryManager))
	{
		inventoryManager->TryGetInventory(InventoryID);

	}
	else
	{
		Debug::Print(DEBUG_TEXT("Inventory Manager is Invalid."));
	}
}

//bool UInventoryComponent::CheckInventoryHasSpace() const
//{
//	//빈 슬롯이 있으면 인벤토리가 비었다고 생각.
//
//	//for (int32 i = 0; i < Items.Num(); i++)
//	//{
//	//	if (Items[i].IsEmpty())
//	//	{
//	//		return true;
//	//	}
//	//}
//
//	return false;
//}
//
//const FItemSlotData* UInventoryComponent::GetInventoryItem(const int32 Index) const
//{
//	//인벤토리 사이즈 이상의 값을 얻으려고 하면 문제가 있을 수도 있음.
//
//	//if (Items.IsValidIndex(Index))
//	//{
//	//	//아이템 위치값? 버그나서 문제 생기면, 구조체 복사로 return하는 걸로 변경할 것.
//	//	return &Items[Index];
//	//}
//
//	////실패.
//	//UE_LOG(LogTemp, Warning, TEXT("Invalid Item Index Requested.."));
//	return nullptr;
//}
//
//bool UInventoryComponent::SetInventoryItem(const int32 Index, const FItemSlotData& InData)
//{
//	if (!Items.IsValidIndex(Index))
//	{
//		return false;
//	}
//
//	Items[Index] = InData;
//	// TODO : 아이템 데이터가 바뀌었음을 알리는 것이 필요함.
//	OnInventoryItemsChanged.Broadcast();
//	return true;
//}
//
//int32 UInventoryComponent::AddItemToInventory(const FItemSlotData& InData)
//{
//	//-1 : 실패 , 0 : 성공 , 1 이상 : 아이템이 남았음.
//
//	if (InData.IsEmpty())
//	{
//		//빈 데이터는 넣지 않음.
//		return -1;
//	}
//
//	//TODO : 아이템 정보를 확인하는 작업 필요함.
//	FItemSheetData itemSheetData; // 데이터 테이블에서 올바른 아이템 정보를 가져와야함.
//
//	FItemSlotData leftover = InData;
//
//	for (int i = 0; i < Items.Num(); i++)
//	{
//		if (!Items[i].IsSameItem(leftover))
//		{
//			continue;
//		}
//
//		//TODO : 아이템 슬롯에 아이템이 최대 stack 채울 수 있는 양보다 공간이 남는지 확인?
//		if(Items[i].Quantity < itemSheetData.MaxQuantity)
//		{
//			int32 extra = itemSheetData.MaxQuantity - Items[i].Quantity;
//			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);
//
//			Items[i].Quantity += tempOffset;
//			leftover.Quantity -= tempOffset;
//
//			if (leftover.Quantity == 0)
//			{
//				//남은게 없으면 성공.
//				OnInventoryItemsChanged.Broadcast();
//				return 0;
//			}
//			else if (leftover.Quantity < 0)
//			{
//				//음수면 문제가 있긴함. 다만, 인벤토리에 반영이 됐으므로 일단 0으로 취급
//				OnInventoryItemsChanged.Broadcast();
//				return 0;
//			}
//		}
//
//	}
//
//	//여기까지 왔다면, leftover의 양이 남아있거나, 혹은 같은 슬롯을 찾지 못함.
//	//빈 공간 있으면 정보를 넣는다.
//	for (int i = 0; i < Items.Num(); i++)
//	{
//		if (Items[i].IsEmpty())
//		{
//			SetInventoryItem(i, leftover);
//			OnInventoryItemsChanged.Broadcast();
//			return 0;
//		}
//	}
//
//	//Warning 1 : leftover의 아이템을 약간 얻었는데, 바닥에 떨어진 아이템 처리가 제대로 되지 않음.
//	//Warning 2 : 보상을 얻으려 했는데, 보상이 초과되서 남음 or 인벤토리 공간이 없어서 보상을 아예 얻지 못함.
//	OnInventoryItemsChanged.Broadcast();
//	return leftover.Quantity;
//
//}
//
//bool UInventoryComponent::UseItemInInventory(const int32 ItemIndex)
//{
//	//TODO : 아이템 종류에 따라 아이템 갯수를 내리거나, 장착하거나... 등등
//
//	return false;
//}
//
//bool UInventoryComponent::UseItemsInInventory(const FName& ItemName, const int32 Quantity)
//{
//
//	bool bEnough = CheckItemWithQuantityInInventory(ItemName, Quantity);
//
//	if (!bEnough)
//	{
//		return false;
//	}
//
//	int32 quantity = Quantity;
//
//	for (int32 i = 0; i < Items.Num(); i++)
//	{
//		int32 currentQuantity = Items[i].Quantity;
//
//		if (quantity == currentQuantity) // 필요한 양과 아이템 슬롯의 양과 같을 때
//		{
//			quantity = 0;
//			Items[i].SetEmpty();
//		}
//		else if (currentQuantity > quantity) //아이템 슬롯의 양이 필요한 양보다 많을 때
//		{
//			int32 temp = currentQuantity - quantity;
//			quantity = 0;
//			Items[i].Quantity = temp;
//		}
//		else //currentQuantity < quantity
//		{
//			quantity -= currentQuantity;
//			Items[i].SetEmpty();
//		}
//
//		if (quantity <= 0) //여기는 무조건 동작할 것이라고 본다.
//		{
//			OnInventoryItemsChanged.Broadcast();
//			return true;
//		}
//	}
//
//	//여기까지 오지 않을 것이라 생각함.
//	//이미 아이템이 존재하는지, 그리고 갯수가 충분한지 검사하고 실행하기 때문이다.
//	return false;
//}
//
//bool UInventoryComponent::CheckItemInInventory(const FName& ItemName) const
//{
//	for (int32 i = 0; i < Items.Num(); i++)
//	{
//		if (ItemName == Items[i].ItemName)
//		{
//			if (Items[i].Quantity > 0)
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//bool UInventoryComponent::CheckItemWithQuantityInInventory(const FName& ItemName, const int32 Quantity) const
//{
//	if (!CheckItemInInventory(ItemName))
//	{
//		return false;
//	}
//
//	int32 quantity = Quantity;
//
//	//같은 아이템 이름의 슬롯을 찾아, 양을 줄여가면서 양이 0 이하의 값이 나온다면 그 아이템의 개수가 충분히 있다는 의미.
//	for (int32 i = 0; i < Items.Num(); i++)
//	{
//		if (Items[i].ItemName == ItemName)
//		{
//			quantity -= Items[i].Quantity;
//			if (quantity <= 0)
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//int32 UInventoryComponent::GetItemQuantity(const FName& ItemName) const
//{
//	//해당 아이템의 총 갯수가 몇개인지 검색.
//	int32 sum = 0;
//
//	for (int32 i = 0; i < Items.Num(); i++)
//	{
//		if (ItemName == Items[i].ItemName)
//		{
//			sum += Items[i].Quantity;
//		}
//	}
//
//	return sum;
//}
//
//TArray<FItemSlotData> UInventoryComponent::GetAllItems() const
//{
//	//아이템 정보 복사본
//	return Items;
//}
//
//void UInventoryComponent::SetInventorySize(const int32 Val)
//{
//	if (Val <= 0)
//	{
//		//잘못된 인벤토리 크기
//		return;
//	}
//
//	InventorySize = Val;
//
//	InitializeInventory();
//}
//
//int32 UInventoryComponent::GetInventorySize() const
//{
//	return InventorySize;
//}
//
//void UInventoryComponent::ExpandInventory(const int32 ExpandSize)
//{
//	if (ExpandSize <= InventorySize)
//	{
//		//올바른 확장 크기가 아님.
//		return;
//	}
//
//	auto prevItems = GetAllItems();
//
//	SetInventorySize(ExpandSize);
//
//	//확장된 인벤토리에 기존 아이템 정보 넣기
//	for (int32 i = 0; i < prevItems.Num(); i++)
//	{
//		Items[i] = prevItems[i];
//	}
//
//	OnInventoryItemsChanged.Broadcast();
//
//}
//
//bool UInventoryComponent::SwapItemBetweenInventory(TObjectPtr<UInventoryComponent> From, const int32 FromSlotIndex, TObjectPtr<UInventoryComponent> To, const int32 ToSlotIndex)
//{
//	if (!(IsValid(From) && IsValid(To)))
//	{
//		//올바른 인벤토리가 아님
//		return false;
//	}
//
//	if (!From->Items.IsValidIndex(FromSlotIndex) || !To->Items.IsValidIndex(ToSlotIndex))
//	{
//		//각 인벤토리의 올바른 index가 아님
//		return false;
//	}
//
//	FItemSlotData i1 = From->Items[FromSlotIndex];
//	FItemSlotData i2 = To->Items[ToSlotIndex];
//
//	//TODO : 아이템 정보를 확인하는 로직이 필요함.
//	FItemSheetData itemSheetData;
//
//	if (i1.ItemName != i2.ItemName) //서로 다른 아이템 -> 서로의 위치를 바꿈
//	{
//		From->Items[FromSlotIndex] = i2;
//		To->Items[ToSlotIndex] = i1;
//
//		From->OnInventoryItemsChanged.Broadcast();
//		To->OnInventoryItemsChanged.Broadcast();
//		return true;
//	}
//	else // 같은 아이템이면 조인한다.
//	{
//
//		if (itemSheetData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot 갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
//		{
//			i1.Quantity += i2.Quantity;
//			i2 = FItemSlotData();
//
//			From->Items[FromSlotIndex] = i2;
//			To->Items[ToSlotIndex] = i1;
//
//			//join1 Success;
//			From->OnInventoryItemsChanged.Broadcast();
//			To->OnInventoryItemsChanged.Broadcast();
//			return true;
//		}
//		else //둘이 합쳐서 최대 수량을 초과하면.. "ToSlot"에는 Max Quantity 만큼 들어감 , "FromSlot"에는 나머지가 들어감.
//		{
//			int32 temp = i1.Quantity + i2.Quantity;
//			i1.Quantity = itemSheetData.MaxQuantity;
//
//			temp -= i1.Quantity;
//			i2.Quantity = temp;
//
//			From->Items[FromSlotIndex] = i2;
//			To->Items[ToSlotIndex] = i1;
//
//			//join2 Success
//			From->OnInventoryItemsChanged.Broadcast();
//			To->OnInventoryItemsChanged.Broadcast();
//			return true;
//		}
//
//	}
//
//	//알수없는 이유로 Swap 실패함. 아마 여기에 오지 않을 것으로 보임.
//	return false;
//}
//
//void UInventoryComponent::InitializeInventory()
//{
//	//인벤토리 공간을 전부 비우고, 빈 아이템 슬롯 정보를 넣는다.
//
//	Items.Empty();
//
//	FItemSlotData slotData;
//
//	for (int32 i = 0; i < InventorySize; i++)
//	{
//		Items.Add(slotData);
//	}
//
//}
//
