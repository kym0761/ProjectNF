// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStrategy/BaseCharacterState.h"
#include "chPlantingState.generated.h"

//작물 심기 기능을 위한 임시 state로, 추후에 변경시 제거될 수 있음.

/**
 * 
 */
UCLASS()
class PROJECTNF_API UchPlantingState : public UBaseCharacterState
{
	GENERATED_BODY()
	
public:

	UchPlantingState();

public:

	virtual void StateAction() override;

};
