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
	//�ִϸ��̼��� ���� ������ ������ ������ �� �� �ְ� Ǯ���ܰ� ���ÿ�
	//�޺� �ʱ�ȭ��.
	bAttackPlayOK = true;
	ComboNumber = ComboNumberMin;
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
