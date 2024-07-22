// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryObject.h"
#include "DebugHelper.h"
#include "System/NFGameInstance.h"
#include "Kismet/GameplayStatics.h"


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

bool UInventoryObject::HasInventoryEmptySpace() const
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

bool UInventoryObject::HasEnoughSpaceForItem(const FItemSlotData& InData) const
{

	// ������ ���̺��� �ùٸ� ������ ������ �����;���.
	FItemSheetData itemSheetData;

	if (!GEngine)
	{
		//GEngine nullptr
		return false;
	}

	auto gameinstance = Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GEngine->GetCurrentPlayWorld()));
	if (!gameinstance)
	{
		//gameinstance nullptr
		return false;
	}

	bool bIsCorrectItemData = gameinstance->GetItemDataFromDataTable(InData.ItemName, itemSheetData);
	if (!bIsCorrectItemData)
	{
		//�ùٸ� ������ ������ �ƴ�.
		return false;
	}

	int32 quantity = InData.Quantity;


	for (int i = 0; i < Items.Num(); i++)
	{
		if (InData.IsSameItem(Items[i]))
		{
			//���������� ���ϰ�, quantity�� ����������ŭ ����.
			int32 margin = itemSheetData.MaxQuantity - InData.Quantity;
			quantity = quantity - margin;
		}
		else if (InData.IsEmpty())
		{
			//�� �����̸� quantity�� MaxQuantity��ŭ ����.
			quantity = quantity - itemSheetData.MaxQuantity;
		}

		if (quantity <= 0)
		{
			//���� ������ ���ø��� ������, ���������� Ȯ���ϴ� �����̶� ������ ���͵� OK.
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

const FItemSlotData* UInventoryObject::GetInventoryItem(const int32 Index) const
{
	//�κ��丮 ������ �̻��� ���� �������� �ϸ� �ȵ�.
	if (Items.IsValidIndex(Index))
	{
		//������ ��ġ��? ���׳��� ���� �����, ����ü ����� return�ϴ� �ɷ� ������ ��.
		return &Items[Index];
	}

	//����.
	Debug::Print(DEBUG_TEXT("Invalid Item Index Requested.."));
	return nullptr;
}

bool UInventoryObject::SetInventoryItem(const int32 Index, const FItemSlotData& InData)
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

int32 UInventoryObject::AddItemToInventory(const FItemSlotData& InData)
{
	//-1 : ���� , 0 : ���� , 1 �̻� : �������� ������.

	if (InData.IsEmpty())
	{
		//�� �����ʹ� ���� ����.
		return -1;
	}

	// ������ ���̺��� �ùٸ� ������ ������ �����;���.
	FItemSheetData itemSheetData;
	
	if (!GEngine)
	{
		//GEngine nullptr
		return -1;
	}

	auto gameinstance= Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GEngine->GetCurrentPlayWorld()));
	if (!gameinstance)
	{
		//gameinstance nullptr
		return -1;
	}

	bool bIsCorrectItemData = gameinstance->GetItemDataFromDataTable(InData.ItemName, itemSheetData);
	if (!bIsCorrectItemData)
	{
		//�ùٸ� ������ ������ �ƴ�.
		return -1;
	}


	FItemSlotData leftover = InData;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (!Items[i].IsSameItem(leftover))
		{
			continue;
		}

		//TODO : ������ ���Կ� �������� �ִ� stack ä�� �� �ִ� �纸�� ������ ������ Ȯ��?
		if (Items[i].Quantity < itemSheetData.MaxQuantity)
		{
			int32 extra = itemSheetData.MaxQuantity - Items[i].Quantity;
			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

			Items[i].Quantity += tempOffset;
			leftover.Quantity -= tempOffset;

			if (leftover.Quantity <= 0)
			{
				//������ �ɸ��� ������, �κ��丮�� �ݿ��� �Ǿ� 0���� �����.
				//������ ������ ����.
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
			SetInventoryItem(i, leftover); //setInventoryItem���� �̹� OnInventoryItemsChanged�� ����
			//OnInventoryItemsChanged.Broadcast();
			return 0;
		}
	}

	//Case 1 : �ٴڿ� ������ �������� �޾Ҵµ�, leftover�� ����.
	//Case 2 : ����Ʈ�� ��Ÿ ������ ������ ������ �ߴµ�, ������ �ʰ��Ǽ� ���� or �κ��丮 ������ ��� ������ �ƿ� ���� ����.
	OnInventoryItemsChanged.Broadcast();
	return leftover.Quantity;
}

bool UInventoryObject::UseItemInInventory(const int32 ItemIndex, const int32 UseQuantity)
{
	//TODO : ������ ������ ���� ������ ������ �����ų�, �����ϰų�... ���

	return false;
}

bool UInventoryObject::UseItemInInventory(const FName& ItemName, const int32 UseQuantity)
{
	bool bEnough = HasEnoughQuantityOfItem(ItemName, UseQuantity);
	if (!bEnough)
	{
		//�������� ����� ���� ������ ����
		return false;
	}

	int32 quantity = UseQuantity;

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

	//�̹� �������� �����ϴ���, �׸��� ������ ������� �˻��ϰ� �����ϱ� ������
	//������� ���� ���� ���̶� ������.
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

bool UInventoryObject::SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex)
{

	if (!(IsValid(FromInventory) && IsValid(ToInventory)))
	{
		//�ùٸ� �κ��丮�� �ƴ�
		return false;
	}

	if (!FromInventory->Items.IsValidIndex(FromIndex) || !ToInventory->Items.IsValidIndex(ToIndex))
	{
		//�� �κ��丮�� �ùٸ� index�� �ƴ�
		return false;
	}

	FItemSlotData i1 = FromInventory->Items[FromIndex];
	FItemSlotData i2 = ToInventory->Items[ToIndex];

	//TODO : ������ ������ Ȯ���ϴ� ������ �ʿ���.
	FItemSheetData itemSheetData;


	if (i1.ItemName != i2.ItemName) //���� �ٸ� ������ -> ������ ��ġ�� �ٲ�
	{
		FromInventory->Items[FromIndex] = i2;
		ToInventory->Items[ToIndex] = i1;

		FromInventory->OnInventoryItemsChanged.Broadcast();
		ToInventory->OnInventoryItemsChanged.Broadcast();
		return true;
	}
	else // ���� �������̸� �����Ѵ�.
	{
		if (itemSheetData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot ������ FromSlot ������ ���� �� ���Կ� �� ������ ����ϸ�.. "ToSlot"�� �������� ���� ��. "FromSlot"�� �� ������ ��.
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
		else //���� ���ļ� �ִ� ������ �ʰ��ϸ�.. "ToSlot"���� Max Quantity ��ŭ �� , "FromSlot"���� �������� ��.
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
