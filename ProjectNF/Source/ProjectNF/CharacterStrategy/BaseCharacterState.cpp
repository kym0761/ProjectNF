// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterState.h"

UBaseCharacterState::UBaseCharacterState()
{
	CharacterStateType = ECharacterStateType::NONE;
}

void UBaseCharacterState::StateAction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald, TEXT("NONE State Action"));
	}

}
