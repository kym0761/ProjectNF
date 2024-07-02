// Fill out your copyright notice in the Description page of Project Settings.


#include "ChFarmingState.h"
#include "BaseCharacter.h"

UChFarmingState::UChFarmingState()
{
	CharacterStateType = ECharacterStateType::FARMING;
}

void UChFarmingState::StateAction()
{
	Super::StateAction();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("FARMING State Action"));
	}

	CharacterRef->UseFarmTool();

}
