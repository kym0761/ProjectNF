// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "DebugHelper.h"
#include "Defines/Data.h"
#include "System/NFGameInstance.h"
UInventoryManager::UInventoryManager()
{
}

UInventoryObject* UInventoryManager::TryGetInventory(FString InventoryOwner)
{
	//if (InventoryOwner.IsEmpty())
	//{
	//	//잘못된 인벤토리 접근법
	//	//InventoryOwner가 ""임.
	//	FMyDebug::Print(DEBUG_TEXT("InventoryOwner String Empty"));
	//	return nullptr;
	//}

	////FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Map Size = %d"), InventoryMap.Num()));

	////InventoryOwner에 대한 인벤토리가 없다면 새로 생성해준다.
	//if (InventoryMap.Num() == 0 
	//	|| !InventoryMap.Contains(InventoryOwner))
	//{
	//	//TODO : 인벤토리 생성시, 지정된 크기 등으로 초기화? 
	//	UInventoryObject* inventory = NewObject<UInventoryObject>(this);
	//	inventory->InitInventory();

	//	inventory->RequestItemSheetData.BindStatic(&UNFGameInstance::GetItemData);

	//	InventoryMap.Add(InventoryOwner, inventory);
	//	FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Created --> InventoryOwner : %s"), *InventoryOwner));
	//	return InventoryMap[InventoryOwner];
	//}
	//else
	//{
	//	FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Exist! --> InventoryOwner : %s"), *InventoryOwner));
	//	return InventoryMap[InventoryOwner];
	//}

	return nullptr;
}

void UInventoryManager::InitManager()
{
	//할 것이 없는 것 같다.
}

void UInventoryManager::LoadInventories(const TArray<FInventorySaveData>& InventorySaveData)
{
	//for (auto& data : InventorySaveData)
	//{
	//	FString inventoryID = data.InventoryID;

	//	UInventoryObject* inventoryObj = NewObject<UInventoryObject>(this);		
	//	inventoryObj->LoadInventory(data.Items);

	//	InventoryMap.Add(inventoryID, inventoryObj);
	//	inventoryObj->RequestItemSheetData.BindStatic(&UNFGameInstance::GetItemData);
	//}
}

TMap<FString, UInventoryObject*>& UInventoryManager::GetAllInventories()
{
	return InventoryMap;
}
