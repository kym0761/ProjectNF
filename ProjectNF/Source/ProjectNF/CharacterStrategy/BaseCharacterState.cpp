// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterState.h"
#include "BaseCharacter.h"

UBaseCharacterState::UBaseCharacterState()
{
	CharacterStateType = ECharacterStateType::NONE;

	//Outer�� Character�� ĳ�����ϰ� �����Ѵ�. �׷��� ���� Outer Cast�ϴ� ���� �� �� ����.
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
