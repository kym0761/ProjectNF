// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "UObject/NoExportTypes.h"
#include "BaseCharacterState.generated.h"

//파생 클래스들 ch 붙인 이유는 언리얼 엔진 어딘가에 이름이 같은 클래스가 존재함
//ch = character임

/**
 * 
 */
UCLASS()
class PROJECTNF_API UBaseCharacterState : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseCharacterState();

	//State의 타입
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterStateType CharacterStateType;

	//Outer == Character
	UPROPERTY(BlueprintReadWrite, Category = "State")
	TObjectPtr<class ABaseCharacter> CharacterRef;

public:

	virtual void StateAction();

};
