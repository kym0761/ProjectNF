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

	OnMontageEnded.AddDynamic(this, &UBaseAnimInstance::OnCombatMontageEnded);
}

void UBaseAnimInstance::OnCombatMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	//��Ÿ���� �ִϸ��̼��� �ð��� �� �Ǿ� �����ٸ�, �޺� �ʱ�ȭ�Ѵ�.
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
	//�ִϸ��̼� ������ �� ������ �߰��� �� ���ϰ� ����
	bAttackPlayOK = false;
}

void UBaseAnimInstance::AnimNotify_AttackComboOk()
{
	//�޺� ������ ������ Ÿ�ֿ̹� ������ �� �� �ְ� Ǯ����
	bAttackPlayOK = true;
}

void UBaseAnimInstance::AnimNotify_AttackEnd()
{
	//�ִϸ��̼��� ���� ������ �������� �޺� ������ �Ұ����ϰ� �ִϸ��̼��� ����Ǳ� ��ٷ����Ѵ�.

	bAttackPlayOK = false;

}

void UBaseAnimInstance::PlayAttackMontage()
{
	//�����㰡�� ���� ������ �Ұ���
	if (!bAttackPlayOK)
	{
		return;
	}

	FName comboName = FName(*FString::Printf(TEXT("Attack%d"), ComboNumber));

	Montage_Play(BaseCombatMontage);
	Montage_JumpToSection(comboName, BaseCombatMontage);

	ComboNumber++;
}
