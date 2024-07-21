// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	InventorySize = 100;

	InitializeInventory();
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//InventorySize�� ���� ������� �� �κ��丮�� ũ�⸦ �ٽ� �������Ѵ�.
	FProperty* prop = PropertyChangedEvent.Property;
	if (prop->GetName() == TEXT("InventorySize"))
	{
		InitializeInventory();
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::CheckInventoryHasSpace() const
{
	//�� ������ ������ �κ��丮�� ����ٰ� ����.

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{
			return true;
		}
	}

	return false;
}

const FItemSlotData* UInventoryComponent::GetInventoryItem(const int32 Index) const
{
	//�κ��丮 ������ �̻��� ���� �������� �ϸ� ������ ���� ���� ����.

	if (Items.IsValidIndex(Index))
	{
		//������ ��ġ��? ���׳��� ���� �����, ����ü ����� return�ϴ� �ɷ� ������ ��.
		return &Items[Index];
	}

	//����.
	UE_LOG(LogTemp, Warning, TEXT("Invalid Item Index Requested.."));
	return nullptr;
}

bool UInventoryComponent::SetInventoryItem(const int32 Index, const FItemSlotData& InData)
{
	if (!Items.IsValidIndex(Index))
	{
		return false;
	}

	Items[Index] = InData;
	// TODO : ������ �����Ͱ� �ٲ������ �˸��� ���� �ʿ���.
	OnInventoryItemsChanged.Broadcast();
	return true;
}

int32 UInventoryComponent::AddItemToInventory(const FItemSlotData& InData)
{
	//-1 : ���� , 0 : ���� , 1 �̻� : �������� ������.

	if (InData.IsEmpty())
	{
		//�� �����ʹ� ���� ����.
		return -1;
	}

	//TODO : ������ ������ Ȯ���ϴ� �۾� �ʿ���.
	FItemSheetData itemSheetData; // ������ ���̺��� �ùٸ� ������ ������ �����;���.

	FItemSlotData leftover = InData;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (!Items[i].IsSameItem(leftover))
		{
			continue;
		}

		//TODO : ������ ���Կ� �������� �ִ� stack ä�� �� �ִ� �纸�� ������ ������ Ȯ��?
		if(Items[i].Quantity < itemSheetData.MaxQuantity)
		{
			int32 extra = itemSheetData.MaxQuantity - Items[i].Quantity;
			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

			Items[i].Quantity += tempOffset;
			leftover.Quantity -= tempOffset;

			if (leftover.Quantity == 0)
			{
				//������ ������ ����.
				OnInventoryItemsChanged.Broadcast();
				return 0;
			}
			else if (leftover.Quantity < 0)
			{
				//������ ������ �ֱ���. �ٸ�, �κ��丮�� �ݿ��� �����Ƿ� �ϴ� 0���� ���
				OnInventoryItemsChanged.Broadcast();
				return 0;
			}
		}

	}

	//������� �Դٸ�, leftover�� ���� �����ְų�, Ȥ�� ���� ������ ã�� ����.
	//�� ���� ������ ������ �ִ´�.
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{
			SetInventoryItem(i, leftover);
			OnInventoryItemsChanged.Broadcast();
			return 0;
		}
	}

	//Warning 1 : leftover�� �������� �ణ ����µ�, �ٴڿ� ������ ������ ó���� ����� ���� ����.
	//Warning 2 : ������ ������ �ߴµ�, ������ �ʰ��Ǽ� ���� or �κ��丮 ������ ��� ������ �ƿ� ���� ����.
	OnInventoryItemsChanged.Broadcast();
	return leftover.Quantity;

}

bool UInventoryComponent::UseItemInInventory(const int32 ItemIndex)
{
	//TODO : ������ ������ ���� ������ ������ �����ų�, �����ϰų�... ���

	return false;
}

bool UInventoryComponent::UseItemsInInventory(const FName& ItemName, const int32 Quantity)
{

	bool bEnough = CheckItemWithQuantityInInventory(ItemName, Quantity);

	if (!bEnough)
	{
		return false;
	}

	int32 quantity = Quantity;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		int32 currentQuantity = Items[i].Quantity;

		if (quantity == currentQuantity) // �ʿ��� ��� ������ ������ ��� ���� ��
		{
			quantity = 0;
			Items[i].SetEmpty();
		}
		else if (currentQuantity > quantity) //������ ������ ���� �ʿ��� �纸�� ���� ��
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

		if (quantity <= 0) //����� ������ ������ ���̶�� ����.
		{
			OnInventoryItemsChanged.Broadcast();
			return true;
		}
	}

	//������� ���� ���� ���̶� ������.
	//�̹� �������� �����ϴ���, �׸��� ������ ������� �˻��ϰ� �����ϱ� �����̴�.
	return false;
}

bool UInventoryComponent::CheckItemInInventory(const FName& ItemName) const
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

bool UInventoryComponent::CheckItemWithQuantityInInventory(const FName& ItemName, const int32 Quantity) const
{
	if (!CheckItemInInventory(ItemName))
	{
		return false;
	}

	int32 quantity = Quantity;

	//���� ������ �̸��� ������ ã��, ���� �ٿ����鼭 ���� 0 ������ ���� ���´ٸ� �� �������� ������ ����� �ִٴ� �ǹ�.
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

int32 UInventoryComponent::GetItemQuantity(const FName& ItemName) const
{
	//�ش� �������� �� ������ ����� �˻�.
	int32 sum = 0;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (ItemName == Items[i].ItemName)
		{
			sum += Items[i].Quantity;
		}
	}

	return sum;
}

TArray<FItemSlotData> UInventoryComponent::GetAllItems() const
{
	//������ ���� ���纻
	return Items;
}

void UInventoryComponent::SetInventorySize(const int32 Val)
{
	if (Val <= 0)
	{
		//�߸��� �κ��丮 ũ��
		return;
	}

	InventorySize = Val;

	InitializeInventory();
}

int32 UInventoryComponent::GetInventorySize() const
{
	return InventorySize;
}

void UInventoryComponent::ExpandInventory(const int32 ExpandSize)
{
	if (ExpandSize <= InventorySize)
	{
		//�ùٸ� Ȯ�� ũ�Ⱑ �ƴ�.
		return;
	}

	auto prevItems = GetAllItems();

	SetInventorySize(ExpandSize);

	//Ȯ��� �κ��丮�� ���� ������ ���� �ֱ�
	for (int32 i = 0; i < prevItems.Num(); i++)
	{
		Items[i] = prevItems[i];
	}

	OnInventoryItemsChanged.Broadcast();

}

bool UInventoryComponent::SwapItemBetweenInventory(TObjectPtr<UInventoryComponent> From, const int32 FromSlotIndex, TObjectPtr<UInventoryComponent> To, const int32 ToSlotIndex)
{
	if (!(IsValid(From) && IsValid(To)))
	{
		//�ùٸ� �κ��丮�� �ƴ�
		return false;
	}

	if (!From->Items.IsValidIndex(FromSlotIndex) || !To->Items.IsValidIndex(ToSlotIndex))
	{
		//�� �κ��丮�� �ùٸ� index�� �ƴ�
		return false;
	}

	FItemSlotData i1 = From->Items[FromSlotIndex];
	FItemSlotData i2 = To->Items[ToSlotIndex];

	//TODO : ������ ������ Ȯ���ϴ� ������ �ʿ���.
	FItemSheetData itemSheetData;

	if (i1.ItemName != i2.ItemName) //���� �ٸ� ������ -> ������ ��ġ�� �ٲ�
	{
		From->Items[FromSlotIndex] = i2;
		To->Items[ToSlotIndex] = i1;

		From->OnInventoryItemsChanged.Broadcast();
		To->OnInventoryItemsChanged.Broadcast();
		return true;
	}
	else // ���� �������̸� �����Ѵ�.
	{

		if (itemSheetData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot ������ FromSlot ������ ���� �� ���Կ� �� ������ ����ϸ�.. "ToSlot"�� �������� ���� ��. "FromSlot"�� �� ������ ��.
		{
			i1.Quantity += i2.Quantity;
			i2 = FItemSlotData();

			From->Items[FromSlotIndex] = i2;
			To->Items[ToSlotIndex] = i1;

			//join1 Success;
			From->OnInventoryItemsChanged.Broadcast();
			To->OnInventoryItemsChanged.Broadcast();
			return true;
		}
		else //���� ���ļ� �ִ� ������ �ʰ��ϸ�.. "ToSlot"���� Max Quantity ��ŭ �� , "FromSlot"���� �������� ��.
		{
			int32 temp = i1.Quantity + i2.Quantity;
			i1.Quantity = itemSheetData.MaxQuantity;

			temp -= i1.Quantity;
			i2.Quantity = temp;

			From->Items[FromSlotIndex] = i2;
			To->Items[ToSlotIndex] = i1;

			//join2 Success
			From->OnInventoryItemsChanged.Broadcast();
			To->OnInventoryItemsChanged.Broadcast();
			return true;
		}

	}

	//�˼����� ������ Swap ������. �Ƹ� ���⿡ ���� ���� ������ ����.
	return false;
}

void UInventoryComponent::InitializeInventory()
{
	//�κ��丮 ������ ���� ����, �� ������ ���� ������ �ִ´�.

	Items.Empty();

	FItemSlotData slotData;

	for (int32 i = 0; i < InventorySize; i++)
	{
		Items.Add(slotData);
	}

}

