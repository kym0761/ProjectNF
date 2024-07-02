// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseCharacterState.generated.h"

//Cast���� �ʰ� ĳ���� State�� �������� �˾Ƴ��� ���� Enum
//State�� �߰��Ѵٸ� �� �߰��� �� CharacterStateType�� �ùٸ� ������ Set�� ��
UENUM(BlueprintType)
enum class  ECharacterStateType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),

	/*�Ϲ� ������ �з�*/
	NORMAL UMETA(DisplayName = "NORMAL"),
	BATTLE UMETA(DisplayName = "BATTLE"),
	FARMING UMETA(DisplayName = "FARMING")

};

/**
 * 
 */
UCLASS()
class PROJECTNF_API UBaseCharacterState : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseCharacterState();

	//State�� Ÿ��
	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECharacterStateType CharacterStateType;

	//Outer == Character
	UPROPERTY(BlueprintReadWrite, Category = "State")
	TObjectPtr<class ABaseCharacter> CharacterRef;

public:

	virtual void StateAction();

};
