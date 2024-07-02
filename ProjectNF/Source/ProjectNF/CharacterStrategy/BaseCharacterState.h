// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseCharacterState.generated.h"

UENUM(BlueprintType)
enum class  ECharacterStateType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),

	/*일반 아이템 분류*/
	NORMAL UMETA(DisplayName = "NORMAL"),
	BATTLE UMETA(DisplayName = "BATTLE"),
	FARMING UMETA(DisplayName = "FARMING")


};

/**
 * 
 */
UCLASS(Abstract)
class PROJECTNF_API UBaseCharacterState : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseCharacterState();

	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterStateType CharacterStateType;


public:

	virtual void StateAction();

};
