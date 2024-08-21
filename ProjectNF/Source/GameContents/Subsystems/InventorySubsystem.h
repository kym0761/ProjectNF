// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventorySubsystem.generated.h"

class UInventoryObject;

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UInventorySubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

#pragma region GameInventory

protected:

	//key : 인벤토리 소유자 , value : 인벤토리
	UPROPERTY()
	TMap<FString, UInventoryObject*> InventoryMap;

public:

	UInventoryObject* TryGetInventory(FString InventoryOwner);
	bool AddItemToTargetInventory(AActor* InventoryOwner, const FItemSlotData& SlotData);
#pragma endregion

public:

	void LoadInventories(const TArray<FInventorySaveData>& InventorySaveData);

	TMap<FString, UInventoryObject*>& GetAllInventories();

};
