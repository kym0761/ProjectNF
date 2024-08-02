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
class GAMESYSTEMS_API UNFSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UNFSaveGame();

	//저장할 게임 데이터
public:

	//플레이어 이름
	UPROPERTY(VisibleAnywhere, Category = "Save")
	FString PlayerName;
	
	//인벤토리 정보
	UPROPERTY()
	TArray<FInventorySaveData> InventorySave;

	// Crop 데이터
	UPROPERTY()
	TArray<FCropSaveData> CropSave;

};
