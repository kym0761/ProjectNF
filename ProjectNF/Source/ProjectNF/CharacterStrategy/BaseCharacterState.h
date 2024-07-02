// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseCharacterState.generated.h"

//Cast하지 않고 캐릭터 State가 무엇인지 알아내기 위한 Enum
//State를 추가한다면 꼭 추가한 뒤 CharacterStateType을 올바른 값으로 Set할 것
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
