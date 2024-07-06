// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	ComboNumber = 1;
	bAttackPlayOK = true;

	//OnMontageend
}

void UBaseAnimInstance::AnimNotify_AttackStart()
{
	//애니메이션 시작할 때 공격을 추가로 더 못하게 막음
	bAttackPlayOK = false;
}

void UBaseAnimInstance::AnimNotify_AttackComboOk()
{
	//콤보 공격이 가능한 타이밍에 공격을 할 수 있게 풀어줌
	bAttackPlayOK = true;
}

void UBaseAnimInstance::AnimNotify_AttackEnd()
{
	//애니메이션이 거의 끝나는 시점에 공격을 할 수 있게 풀어줌과 동시에
	//콤보 초기화함.
	bAttackPlayOK = true;
	ComboNumber = ComboNumberMin;
}

void UBaseAnimInstance::PlayAttackMontage()
{
	//공격허가가 나지 않으면 불가능
	if (!bAttackPlayOK)
	{
		return;
	}

	FName comboName = FName(*FString::Printf(TEXT("Attack%d"), ComboNumber));

	Montage_Play(BaseCombatMontage);
	Montage_JumpToSection(comboName, BaseCombatMontage);

	ComboNumber++;
}
