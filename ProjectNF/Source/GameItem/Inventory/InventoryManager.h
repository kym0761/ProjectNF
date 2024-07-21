// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces.h"
#include "InventoryManager.generated.h"

class UInventoryObject;

/**
 * 
 */
UCLASS()
class GAMEITEM_API UInventoryManager : public UObject, public IManageable
{
	GENERATED_BODY()
	
public:

	UInventoryManager();

#pragma region GameInventory

protected:

	//key : �κ��丮 ������ , value : �κ��丮
	UPROPERTY()
	TMap<FString, TObjectPtr<UInventoryObject>> InventoryMap;

public:

	TObjectPtr<UInventoryObject> GetInventory(FString InventoryOwner);

#pragma endregion

public:

	virtual void ManagerInit() override;

};
