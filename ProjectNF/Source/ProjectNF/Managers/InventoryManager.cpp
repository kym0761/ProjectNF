// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "Inventory/InventoryObject.h"

UInventoryManager::UInventoryManager()
{
}

TObjectPtr<UInventoryObject> UInventoryManager::GetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//잘못된 인벤토리 접근법
		return nullptr;
	}

	//TODO : 인벤토리 Owner 자체가 존재하는지부터..
	if (!InventoryMap.Contains(InventoryOwner))
	{
		//TODO : 인벤토리 생성시, 지정된 크기 등으로 초기화? 
		UInventoryObject* inventory = NewObject<UInventoryObject>(this);
		inventory->InitInventory();

		InventoryMap[InventoryOwner] = inventory;
	}


	return InventoryMap[InventoryOwner];
}

void UInventoryManager::InitManager()
{
	//?
}
