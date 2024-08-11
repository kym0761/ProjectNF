// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFGameModeBase.generated.h"

/**
 * 이 게임모드 Base는 GameInstance를 Init하는 기능을 가지고 있음.
 */
UCLASS()
class GAMESYSTEMS_API ANFGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ANFGameModeBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	void CreateAllSavedCrop();

	void SetExistItemsInMap();

};
