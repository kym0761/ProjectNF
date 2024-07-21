// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryObject.h"

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
	FItemBaseData itemBaseData;


	if (i1.ItemName != i2.ItemName) //���� �ٸ� ������ -> ������ ��ġ�� �ٲ�
	{
		FromInventory->Items[FromIndex] = i2;
		ToInventory->Items[ToIndex] = i1;

		//FromInventory->OnInventoryItemsChanged.Broadcast();
		//ToInventory->OnInventoryItemsChanged.Broadcast();
		return true;
	}
	else // ���� �������̸� �����Ѵ�.
	{
		if (itemBaseData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot ������ FromSlot ������ ���� �� ���Կ� �� ������ ����ϸ�.. "ToSlot"�� �������� ���� ��. "FromSlot"�� �� ������ ��.
		{
			i1.Quantity += i2.Quantity;
			i2 = FItemSlotData();

			FromInventory->Items[FromIndex] = i2;
			ToInventory->Items[ToIndex] = i1;

			////join1 Success;
			//FromInventory->OnInventoryItemsChanged.Broadcast();
			//ToInventory->OnInventoryItemsChanged.Broadcast();
			return true;
		}
		else //���� ���ļ� �ִ� ������ �ʰ��ϸ�.. "ToSlot"���� Max Quantity ��ŭ �� , "FromSlot"���� �������� ��.
		{
			int32 temp = i1.Quantity + i2.Quantity;
			i1.Quantity = itemBaseData.MaxQuantity;

			temp -= i1.Quantity;
			i2.Quantity = temp;

			FromInventory->Items[FromIndex] = i2;
			ToInventory->Items[ToIndex] = i1;

			////join2 Success
			//FromInventory->OnInventoryItemsChanged.Broadcast();
			//ToInventory->OnInventoryItemsChanged.Broadcast();
			return true;
		}

	}

	return false;
}
