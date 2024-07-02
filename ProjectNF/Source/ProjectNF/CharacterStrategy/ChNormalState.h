// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterState.h"
#include "ChNormalState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UChNormalState : public UBaseCharacterState
{
	GENERATED_BODY()
public:
	UChNormalState();

public:

	virtual void StateAction() override;
};
