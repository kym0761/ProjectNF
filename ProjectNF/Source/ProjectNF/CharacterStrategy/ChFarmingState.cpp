// Fill out your copyright notice in the Description page of Project Settings.


#include "ChFarmingState.h"

UChFarmingState::UChFarmingState()
{
	CharacterStateType = ECharacterStateType::FARMING;
}

void UChFarmingState::StateAction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("FARMING State Action"));
	}
}
