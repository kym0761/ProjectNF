// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStrategy/BaseCharacterState.h"
#include "chPlantingState.generated.h"

//�۹� �ɱ� ����� ���� �ӽ� state��, ���Ŀ� ����� ���ŵ� �� ����.

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
