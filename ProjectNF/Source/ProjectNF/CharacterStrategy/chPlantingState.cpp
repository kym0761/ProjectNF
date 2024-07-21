// Fill out your copyright notice in the Description page of Project Settings.


#include "chPlantingState.h"
#include "BaseCharacter.h"

UchPlantingState::UchPlantingState()
{
	CharacterStateType = ECharacterStateType::PLANTING;
}

void UchPlantingState::StateAction()
{
	Super::StateAction();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 3.0f, FColor::Emerald,
			TEXT("Planting State Action"));
	}

	CharacterRef->DoPlanting();
}
