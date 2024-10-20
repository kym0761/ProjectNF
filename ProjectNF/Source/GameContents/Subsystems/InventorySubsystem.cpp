// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySubsystem.h"
#include "DebugHelper.h"
#include "GameItem/Inventory/InventoryObject.h"
#include "GameItem/Inventory/InventoryComponent.h"
//#include "System/NFGameInstance.h"
#include "Subsystems/SheetDataSubsystem.h"
UInventorySubsystem::UInventorySubsystem()
{
}

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();

}

UInventoryObject* UInventorySubsystem::TryGetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//잘못된 인벤토리 접근법
		//InventoryOwner가 ""임.
		FMyDebug::Print(DEBUG_TEXT("InventoryOwner String Empty"));
		return nullptr;
	}

	//FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Map Size = %d"), InventoryMap.Num()));

	//InventoryOwner에 대한 인벤토리가 없다면 새로 생성해준다.
	if (InventoryMap.Num() == 0
		|| !InventoryMap.Contains(InventoryOwner))
	{
		//TODO : 인벤토리 생성시, 지정된 크기 등으로 초기화? 
		UInventoryObject* inventory = NewObject<UInventoryObject>(this);
		inventory->InitInventory();

		auto sheetDataSubsystem = GetGameInstance()->GetSubsystem<USheetDataSubsystem>();

		inventory->RequestItemSheetData.BindUObject(sheetDataSubsystem, &USheetDataSubsystem::GetItemData);

		InventoryMap.Add(InventoryOwner, inventory);
		//FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Created -> InventoryOwner : %s"), *InventoryOwner));
	}
	else
	{
		//FMyDebug::Print(DEBUG_VATEXT(TEXT("Inventory Exist! -> InventoryOwner : %s"), *InventoryOwner));
	}

	return InventoryMap[InventoryOwner];
}

bool UInventorySubsystem::AddItemToTargetInventory(AActor* InventoryOwner, const FItemSlotData& SlotData)
{
	//인벤토리를 찾고, 인벤토리에 아이템을 넣는다.

	auto inventoryComponent = InventoryOwner->FindComponentByClass<UInventoryComponent>();

	if (!IsValid(inventoryComponent))
	{
		FMyDebug::Print(DEBUG_TEXT("No Inventory comp."));
		return false;
	}

	bool bAdded = inventoryComponent->AddItemToInventory(SlotData);

	return bAdded;
}

void UInventorySubsystem::LoadInventories(const TArray<FInventorySaveData>& InventorySaveData)
{
	//저장된 인벤토리 아이템 정보를 불러오기

	auto sheetDataSubsystem = GetGameInstance()->GetSubsystem<USheetDataSubsystem>();

	for (auto& data : InventorySaveData)
	{
		FString inventoryID = data.InventoryID;

		UInventoryObject* inventoryObj = NewObject<UInventoryObject>(this);
		inventoryObj->LoadInventory(data.Items);

		InventoryMap.Add(inventoryID, inventoryObj);

		inventoryObj->RequestItemSheetData.BindUObject(sheetDataSubsystem, &USheetDataSubsystem::GetItemData);
	}
}

TMap<FString, UInventoryObject*>& UInventorySubsystem::GetAllInventories()
{
	return InventoryMap;
}