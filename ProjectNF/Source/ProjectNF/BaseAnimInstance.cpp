// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "DebugHelper.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	ComboNumber = 1;
	bAttackPlayOK = true;


}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OnMontageEnded.Clear();
	OnMontageEnded.AddDynamic(this, &UBaseAnimInstance::OnCombatMontageEnded);
}

void UBaseAnimInstance::OnCombatMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	//몽타주의 애니메이션이 시간이 다 되어 끝났다면, 콤보 초기화한다.
	if (!bInterrupted)
	{
		bAttackPlayOK = true;
		ComboNumber = ComboNumberMin;
	}

	if (bInterrupted)
	{
		Debug::Print(DEBUG_TEXT("OnMontageEnded, interrupted"));
	}
	else
	{
		Debug::Print(DEBUG_TEXT("OnMontageEnded, not interrupted"));
	}

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
	//애니메이션이 거의 끝나는 시점에는 콤보 공격이 불가능하고 애니메이션이 종료되길 기다려야한다.

	bAttackPlayOK = false;

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
