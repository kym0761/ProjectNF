// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.generated.h"

//파생 클래스들 ch 붙인 이유는 언리얼 엔진 어딘가에 이름이 같은 클래스가 존재함
//ch = character임

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
