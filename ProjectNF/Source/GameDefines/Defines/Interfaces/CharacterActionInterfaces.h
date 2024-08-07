// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterActionInterfaces.generated.h"



/*
*
*/

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class GAMEDEFINES_API UCharacterAction : public UInterface
{
	GENERATED_BODY()
};

//플레이어가 가능한 Action.
class GAMEDEFINES_API ICharacterAction
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void BattleAction() = 0;

	virtual void PlantingAction() = 0;

	virtual void NormalAction() = 0;

	virtual void FarmingAction() = 0;

};

