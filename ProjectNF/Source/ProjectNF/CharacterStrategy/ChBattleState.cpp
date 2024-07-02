// Fill out your copyright notice in the Description page of Project Settings.


#include "ChBattleState.h"

UChBattleState::UChBattleState()
{
	CharacterStateType = ECharacterStateType::BATTLE;
}

void UChBattleState::StateAction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("BATTLE State Action"));
	}
}
