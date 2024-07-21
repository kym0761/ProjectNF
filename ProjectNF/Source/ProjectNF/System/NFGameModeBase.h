// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFGameModeBase.generated.h"

/**
 * GameModeBase에 Manager들을 추가하면, 게임모드에서 Manager를 접근 가능함.
 */
UCLASS()
class PROJECTNF_API ANFGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ANFGameModeBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
