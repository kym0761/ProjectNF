// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterState.h"
#include "BaseCharacter.h"

UBaseCharacterState::UBaseCharacterState()
{
	CharacterStateType = ECharacterStateType::NONE;

	//Outer를 Character로 캐스팅하고 세팅한다. 그러면 이후 Outer Cast하는 수고를 덜 수 있음.
	CharacterRef = Cast<ABaseCharacter>(GetOuter());
}

void UBaseCharacterState::StateAction()
{

	//auto outer = GetOuter();
	//if (IsValid(outer))
	//{
	//	if (GEngine)
	//	{
	//		FString str = FString::Printf(TEXT("State's Owner %s"), *outer->GetName());

	//		GEngine->AddOnScreenDebugMessage(
	//			FMath::Rand(), 3.0f, FColor::Emerald,
	//			str);
	//	}
	//}


}
