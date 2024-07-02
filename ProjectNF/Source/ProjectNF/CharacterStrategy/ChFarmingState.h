// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterState.h"
#include "ChFarmingState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UChFarmingState : public UBaseCharacterState
{
	GENERATED_BODY()
	
public:
	UChFarmingState();

public:

	virtual void StateAction() override;

};
