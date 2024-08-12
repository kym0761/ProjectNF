// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryObject.h"
#include "DebugHelper.h"

UInventoryObject::UInventoryObject()
{

}

void UInventoryObject::InitInventory()
{
	FItemSlotData emptySlot;

	for (int32 i = 0; i < InventorySize; i++)
	{
		Items.Add(emptySlot);
	}

}

void UInventoryObject::LoadInventory(const TArray<FItemSlotData>& InSlots)
{
	Items = InSlots;
}

bool UInventoryObject::HasInventoryEmptySpace() const
{
	//빈 슬롯이 있으면 인벤토리가 비었다고 생각.

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{
			return true;
		}
	}

	return false;
}

bool UInventoryObject::HasEnoughSpaceForItem(const FItemSlotData& InData) const
{

	if (!RequestItemSheetData.IsBound())
	{
		FMyDebug::Print(DEBUG_TEXT("OnRequest is Not Bound"));
		return false;
	}

	// 데이터 테이블에서 올바른 아이템 정보를 가져와야함.
	FItemSheetData itemSheetData = RequestItemSheetData.Execute(InData.ItemName);
	if (itemSheetData.IsEmpty())
	{
		//올바른 아이템 정보가 아님.
		FMyDebug::Print(DEBUG_TEXT("Item Sheet Data is Not Correct"));
		return false;
	}

	int32 quantity = InData.Quantity;


	for (int i = 0; i < Items.Num(); i++)
	{
		if (InData.IsSameItem(Items[i]))
		{
			//여유공간을 구하고, quantity를 여유공간만큼 뺀다.
			int32 margin = itemSheetData.MaxQuantity - InData.Quantity;
			quantity = quantity - margin;
		}
		else if (InData.IsEmpty())
		{
			//빈 공간이면 quantity를 MaxQuantity만큼 뺀다.
			quantity = quantity - itemSheetData.MaxQuantity;
		}

		if (quantity <= 0)
		{
			//양이 음수가 나올리는 없지만, 여유공간만 확인하는 로직이라 음수가 나와도 OK.
			return true;
		}
	}

	return false;
}

bool UInventoryObject::HasItemInInventory(const FName& ItemName) const
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (ItemName == Items[i].ItemName)
		{
			if (Items[i].Quantity > 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool UInventoryObject::HasEnoughQuantityOfItem(const FName& ItemName, const int32 Quantity) const
{
	if (!HasItemInInventory(ItemName))
	{
		return false;
	}

	int32 quantity = Quantity;

	//같은 아이템 이름의 슬롯을 찾아, 양을 줄여가면서 양이 0 이하의 값이 나온다면 그 아이템의 개수가 충분히 있다는 의미.
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemName == ItemName)
		{
			quantity -= Items[i].Quantity;
			if (quantity <= 0)
			{
				return true;
			}
		}
	}

	return false;
}

const FItemSlotData* UInventoryObject::GetInventoryItem(const int32 Index) const
{
	//인벤토리 사이즈 이상의 값을 얻으려고 하면 안됨.
	if (Items.IsValidIndex(Index))
	{
		//아이템 위치값? 버그나서 문제 생기면, 구조체 복사로 return하는 걸로 변경할 것.
		return &Items[Index];
	}

	//실패.
	FMyDebug::Print(DEBUG_TEXT("Invalid Item Index Requested.."));
	return nullptr;
}

bool UInventoryObject::SetInventoryItem(const int32 Index, const FItemSlotData& InData)
{
	if (!Items.IsValidIndex(Index))
	{
		return false;
	}

	Items[Index] = InData;
	// TODO : 아이템 데이터가 바뀌었음을 알리는 것이 필요함.
	OnInventoryItemsChanged.Broadcast();
	return true;
}

int32 UInventoryObject::AddItemToInventory(const FItemSlotData& InData)
{
	//-1 : 실패 , 0 : 성공 , 1 이상 : 아이템이 남았음.

	if (InData.IsEmpty())
	{
		//빈 데이터는 넣지 않음.
		FMyDebug::Print(DEBUG_TEXT("빈 데이터"));
		return -1;
	}

	if (!RequestItemSheetData.IsBound())
	{
		FMyDebug::Print(DEBUG_TEXT("OnRequest is Not Bound"));
		return -1;
	}


	// 데이터 테이블에서 올바른 아이템 정보를 가져와야함.
	FItemSheetData itemSheetData = RequestItemSheetData.Execute(InData.ItemName);
	if (itemSheetData.IsEmpty())
	{
		//올바른 아이템 정보가 아님.
		FMyDebug::Print(DEBUG_TEXT("Item Sheet Data is Not Correct"));
		return -1;
	}


	FItemSlotData leftover = InData;

	for (int i = FreeInventoryStart; i < Items.Num(); i++)
	{
		if (!Items[i].IsSameItem(leftover))
		{
			continue;
		}

		//TODO : 아이템 슬롯에 아이템이 최대 stack 채울 수 있는 양보다 공간이 남는지 확인?
		if (Items[i].Quantity < itemSheetData.MaxQuantity)
		{
			int32 extra = itemSheetData.MaxQuantity - Items[i].Quantity;
			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

			Items[i].Quantity += tempOffset;
			leftover.Quantity -= tempOffset;

			if (leftover.Quantity <= 0)
			{
				//음수가 될리는 없지만, 인벤토리에 반영이 되어 0으로 취급함.
				//남은게 없으면 성공.
				OnInventoryItemsChanged.Broadcast();
				return 0;
			}
		}
	}

	//여기까지 왔다면, leftover의 양이 남아있거나, 혹은 같은 슬롯을 찾지 못함.
	//빈 공간 있으면 정보를 넣는다.
	for (int i = FreeInventoryStart; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{ 
			Items[i].ItemName = leftover.ItemName;
			Items[i].Quantity = leftover.Quantity;
			leftover.Quantity = 0;

			//SetInventoryItem(i, leftover);
			//setInventoryItem에는 이미 OnInventoryItemsChanged가 있음
			OnInventoryItemsChanged.Broadcast();
			
			return 0;
		}
	}

	//Case 1 : 바닥에 떨어진 아이템을 받았는데, leftover가 남음.
	//Case 2 : 퀘스트나 기타 사유로 보상을 얻으려 했는데, 보상이 초과되서 남음 or 인벤토리 공간이 없어서 보상을 아예 얻지 못함.
	OnInventoryItemsChanged.Broadcast();
	return leftover.Quantity;
}

bool UInventoryObject::UseItemInInventory(const int32 ItemIndex, const int32 UseQuantity)
{
	//TODO : 아이템 종류에 따라 아이템 갯수를 내리거나, 장착하거나... 등등
	if (!Items.IsValidIndex(ItemIndex))
	{
		//아이템 인덱스가 유효하지 않음.
		return false;
	}
	
	bool bEnough = (Items[ItemIndex].Quantity >= UseQuantity);
	if (!bEnough)
	{
		//아이템이 충분히 있지 않으면 실패
		return false;
	}

	Items[ItemIndex].Quantity -= UseQuantity;
	if (Items[ItemIndex].Quantity <= 0)
	{
		Items[ItemIndex] = FItemSlotData();
	}

	OnInventoryItemsChanged.Broadcast();
	return true;
}

bool UInventoryObject::UseItemInInventory(const FName& ItemName, const int32 UseQuantity)
{
	bool bEnough = HasEnoughQuantityOfItem(ItemName, UseQuantity);
	if (!bEnough)
	{
		//아이템이 충분히 있지 않으면 실패
		return false;
	}

	int32 quantity = UseQuantity;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		int32 currentQuantity = Items[i].Quantity;

		if (quantity == currentQuantity) // 필요한 양과 아이템 슬롯의 양과 같을 때
		{
			quantity = 0;
			Items[i].SetEmpty();
		}
		else if (currentQuantity > quantity) //아이템 슬롯의 양이 필요한 양보다 많을 때
		{
			int32 temp = currentQuantity - quantity;
			quantity = 0;
			Items[i].Quantity = temp;
		}
		else //currentQuantity < quantity
		{
			quantity -= currentQuantity;
			Items[i].SetEmpty();
		}

		if (quantity <= 0) //여기는 무조건 동작할 것이라고 본다.
		{
			OnInventoryItemsChanged.Broadcast();
			return true;
		}
	}

	//이미 아이템이 존재하는지, 그리고 갯수가 충분한지 검사하고 실행하기 때문에
	//여기까지 오지 않을 것이라 생각함.
	return false;
}

TArray<FItemSlotData>& UInventoryObject::GetAllItems()
{
	return Items;
}

int32 UInventoryObject::GetInventorySize() const
{
	return InventorySize;
}

int32 UInventoryObject::GetFreeInventoryStart() const
{
	return FreeInventoryStart;
}


bool UInventoryObject::SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex)
{

	if (!(IsValid(FromInventory) && IsValid(ToInventory)))
	{
		//올바른 인벤토리가 아님
		return false;
	}

	if (!FromInventory->Items.IsValidIndex(FromIndex) || !ToInventory->Items.IsValidIndex(ToIndex))
	{
		//각 인벤토리의 올바른 index가 아님
		return false;
	}

	FItemSlotData i1 = FromInventory->Items[FromIndex];
	FItemSlotData i2 = ToInventory->Items[ToIndex];

	//TODO : 아이템 정보를 확인하는 로직이 필요함.
	FItemSheetData itemSheetData;


	if (i1.ItemName != i2.ItemName) //서로 다른 아이템 -> 서로의 위치를 바꿈
	{
		FromInventory->Items[FromIndex] = i2;
		ToInventory->Items[ToIndex] = i1;

		FromInventory->OnInventoryItemsChanged.Broadcast();
		ToInventory->OnInventoryItemsChanged.Broadcast();
		return true;
	}
	else // 같은 아이템이면 조인한다.
	{
		if (itemSheetData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot 갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
		{
			i1.Quantity += i2.Quantity;
			i2 = FItemSlotData();

			FromInventory->Items[FromIndex] = i2;
			ToInventory->Items[ToIndex] = i1;

			//join1 Success;
			FromInventory->OnInventoryItemsChanged.Broadcast();
			ToInventory->OnInventoryItemsChanged.Broadcast();
			return true;
		}
		else //둘이 합쳐서 최대 수량을 초과하면.. "ToSlot"에는 Max Quantity 만큼 들어감 , "FromSlot"에는 나머지가 들어감.
		{
			int32 temp = i1.Quantity + i2.Quantity;
			i1.Quantity = itemSheetData.MaxQuantity;

			temp -= i1.Quantity;
			i2.Quantity = temp;

			FromInventory->Items[FromIndex] = i2;
			ToInventory->Items[ToIndex] = i1;

			//join2 Success
			FromInventory->OnInventoryItemsChanged.Broadcast();
			ToInventory->OnInventoryItemsChanged.Broadcast();
			return true;
		}

	}

	return false;
}