// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory/InventoryObject.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "InventoryManager.generated.h"

//class UInventoryObject;

struct FInventorySaveData;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEMANAGERS_API UInventoryManager : public UObject, public IManageable
{
	GENERATED_BODY()
	
public:

	UInventoryManager();

#pragma region GameInventory

protected:

	//key : 인벤토리 소유자 , value : 인벤토리
	UPROPERTY()
	TMap<FString, UInventoryObject*> InventoryMap;

public:

	UInventoryObject* TryGetInventory(FString InventoryOwner);

#pragma endregion

public:

	virtual void InitManager() override;


	void LoadInventories(const TArray<FInventorySaveData>& InventorySaveData);

	const TMap<FString, UInventoryObject*>& GetAllInventories() const;

};
