// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "AbilityAOE.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API AAbilityAOE : public AAbilityBase
{
	GENERATED_BODY()
	
public:

	AAbilityAOE();

protected:

	//광역기 Target 감지용도
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

public:

	virtual void InitAbility_Implementation(AActor* AbilityOwnerVal);

	//어빌리티 시작하기
	virtual void StartAbility_Implementation();

	//어빌리티 끝마치기
	virtual void EndAbility_Implementation();

};
