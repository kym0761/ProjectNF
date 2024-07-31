// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "DebugHelper.h"
#include "Defines/Data.h"

UInventoryManager::UInventoryManager()
{
}

UInventoryObject* UInventoryManager::TryGetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//잘못된 인벤토리 접근법
		//InventoryOwner가 ""임.
		Debug::Print(DEBUG_TEXT("InventoryOwner String Empty"));
		return nullptr;
	}

	Debug::Print(DEBUG_VATEXT(TEXT("Inventory Map Size = %d"), InventoryMap.Num()));

	//InventoryOwner에 대한 인벤토리가 없다면 새로 생성해준다.
	if (InventoryMap.Num() == 0 
		|| !InventoryMap.Contains(InventoryOwner))
	{
		//TODO : 인벤토리 생성시, 지정된 크기 등으로 초기화? 
		UInventoryObject* inventory = NewObject<UInventoryObject>(this);
		inventory->InitInventory();

		InventoryMap.Add(InventoryOwner, inventory);
		Debug::Print(DEBUG_VATEXT(TEXT("Inventory Created --> InventoryOwner : %s"), *InventoryOwner));
		return InventoryMap[InventoryOwner];
	}
	else
	{
		Debug::Print(DEBUG_VATEXT(TEXT("Inventory Exist! --> InventoryOwner : %s"), *InventoryOwner));
		return InventoryMap[InventoryOwner];
	}


}

void UInventoryManager::InitManager()
{
	//?
}

void UInventoryManager::LoadInventories(const TArray<FInventorySaveData>& InventorySaveData)
{
	for (auto& data : InventorySaveData)
	{
		FString inventoryID = data.InventoryID;

		UInventoryObject* inventoryObj = NewObject<UInventoryObject>(this);		
		inventoryObj->LoadInventory(data.Items);

		InventoryMap.Add(inventoryID, inventoryObj);
	}
}

const TMap<FString, UInventoryObject*>& UInventoryManager::GetAllInventories() const
{
	return InventoryMap;
}
