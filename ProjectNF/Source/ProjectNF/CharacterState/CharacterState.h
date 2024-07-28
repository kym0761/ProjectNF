// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UCharacterState : public UObject
{
	GENERATED_BODY()
	
public:
	UCharacterState();

	//State의 타입
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterStateType CharacterStateType;

	//Outer == Character
	UPROPERTY(BlueprintReadWrite, Category = "State")
	TObjectPtr<class AActor> StateOwner;

public:

	virtual void StateAction();

	//Character BP에서 1 2 3 4 눌러서 사용중
	UFUNCTION(Blueprintcallable)
	void SetStateType(ECharacterStateType InputStateType);

};
