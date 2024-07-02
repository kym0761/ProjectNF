// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterState.h"
#include "ChBattleState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UChBattleState : public UBaseCharacterState
{
	GENERATED_BODY()
	
public:
	UChBattleState();

public:

	virtual void StateAction() override;

};
