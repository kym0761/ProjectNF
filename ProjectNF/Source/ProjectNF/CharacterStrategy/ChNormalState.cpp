// Fill out your copyright notice in the Description page of Project Settings.


#include "ChNormalState.h"
#include "BaseCharacter.h"

UChNormalState::UChNormalState()
{
	CharacterStateType = ECharacterStateType::NORMAL;
}

void UChNormalState::StateAction()
{
	Super::StateAction();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("NORMAL State Action"));
	}

	CharacterRef->DoWhat();
}
