// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "AbilityUseItem.generated.h"

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API AAbilityUseItem : public AAbilityBase
{
	GENERATED_BODY()
	
public:

	AAbilityUseItem();

public:

	virtual void InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal = nullptr) override;

	//어빌리티 시작하기
	virtual void StartAbility_Implementation() override;

	//어빌리티 끝마치기
	virtual void EndAbility_Implementation() override;
};
