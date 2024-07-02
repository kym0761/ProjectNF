// Fill out your copyright notice in the Description page of Project Settings.


#include "ChBattleState.h"
#include "BaseCharacter.h"

UChBattleState::UChBattleState()
{
	CharacterStateType = ECharacterStateType::BATTLE;
}

void UChBattleState::StateAction()
{
	Super::StateAction(); //debug ¿ëµµ

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("BATTLE State Action"));
	}

	CharacterRef->Attack();
}
