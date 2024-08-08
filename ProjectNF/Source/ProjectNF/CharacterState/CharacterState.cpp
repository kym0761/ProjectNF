// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterState.h"
#include "Defines/Interfaces/CharacterActionInterfaces.h"
#include "DebugHelper.h"

UCharacterState::UCharacterState()
{
	CharacterStateType = ECharacterStateType::NONE;

	//Outer를 Character로 캐스팅하고 세팅한다. 그러면 이후 Outer Cast하는 수고를 덜 수 있음.
	StateOwner = Cast<AActor>(GetOuter());
}

void UCharacterState::StateAction()
{

	ICharacterAction* characterActionInterface = Cast<ICharacterAction>(StateOwner);
	if (!characterActionInterface)
	{
		FMyDebug::Print(DEBUG_TEXT("character action interface is Invalid."));
		return;
	}

	switch (CharacterStateType)
	{
	case ECharacterStateType::NONE:
		//아무것도 안함.
		break;
	case ECharacterStateType::NORMAL:
		characterActionInterface->NormalAction();
		break;
	case ECharacterStateType::BATTLE:
		characterActionInterface->BattleAction();
		break;
	case ECharacterStateType::FARMING:
		characterActionInterface->FarmingAction();
		break;
	case ECharacterStateType::PLANTING:
		characterActionInterface->PlantingAction();
		break;
	default:
		break;
	}


}

void UCharacterState::SetStateType(ECharacterStateType InputStateType)
{
	if (CharacterStateType == InputStateType)
	{
		return;
	}

	CharacterStateType = InputStateType;
	//TODO : State가 바뀌었을 때 알림.
}
