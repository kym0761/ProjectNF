// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFGameModeBase.generated.h"

/**
 * GameModeBase�� Manager���� �߰��ϸ�, ���Ӹ�忡�� Manager�� ���� ������.
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
