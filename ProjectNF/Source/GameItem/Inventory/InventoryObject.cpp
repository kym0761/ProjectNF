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
	FItemBaseData itemBaseData;


	if (i1.ItemName != i2.ItemName) //서로 다른 아이템 -> 서로의 위치를 바꿈
	{
		FromInventory->Items[FromIndex] = i2;
		ToInventory->Items[ToIndex] = i1;

		//FromInventory->OnInventoryItemsChanged.Broadcast();
		//ToInventory->OnInventoryItemsChanged.Broadcast();
		return true;
	}
	else // 같은 아이템이면 조인한다.
	{
		if (itemBaseData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot 갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
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
		else //둘이 합쳐서 최대 수량을 초과하면.. "ToSlot"에는 Max Quantity 만큼 들어감 , "FromSlot"에는 나머지가 들어감.
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
