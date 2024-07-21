// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "UObject/NoExportTypes.h"
#include "BaseCharacterState.generated.h"

//�Ļ� Ŭ������ ch ���� ������ �𸮾� ���� ��򰡿� �̸��� ���� Ŭ������ ������
//ch = character��

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
