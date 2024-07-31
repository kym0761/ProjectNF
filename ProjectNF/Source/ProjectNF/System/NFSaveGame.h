// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Defines/Data.h"
#include "NFSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UNFSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UNFSaveGame();


	//slot info
public:

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Save")
	int32 SaveSlotUserIndex;


	//game data to save
public:

	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString PlayerName;
	

	UPROPERTY()
	TArray<FInventorySaveData> InventorySave;

};
