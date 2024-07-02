// Fill out your copyright notice in the Description page of Project Settings.


#include "ChNormalState.h"

UChNormalState::UChNormalState()
{
	CharacterStateType = ECharacterStateType::NORMAL;
}

void UChNormalState::StateAction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("NORMAL State Action"));
	}
}
