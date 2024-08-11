// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include "DebugHelper.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"

#include "Ability/AbilityBase.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	ComboNumber = 1;
	bAttackPlayOK = true;

	AbilitySuffix = TEXT("");
}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (APawn* pawn = TryGetPawnOwner())
	{
		AbilitySuffix = pawn->GetClass()->GetName();
		AbilitySuffix.RemoveFromStart(TEXT("BP_"));
		AbilitySuffix.RemoveFromEnd(TEXT("_C"));

		FMyDebug::Print(DEBUG_VATEXT(TEXT("Suffix : %s"), *AbilitySuffix));
	}

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
		FMyDebug::Print(DEBUG_TEXT("OnMontageEnded, interrupted"));
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("OnMontageEnded, not interrupted"));
	}

}

void UBaseAnimInstance::AnimNotify_AttackStart()
{
	//애니메이션 시작할 때 공격을 추가로 더 못하게 막음
	bAttackPlayOK = false;

	if (OnStartAbility.IsBound())
	{
		OnStartAbility.Broadcast();
	}
	
}

void UBaseAnimInstance::AnimNotify_AttackComboOk()
{
	//콤보 공격이 가능한 타이밍에 공격을 할 수 있게 풀어줌
	bAttackPlayOK = true;

	if (OnEndAbility.IsBound())
	{
		OnEndAbility.Broadcast();
	}
}

void UBaseAnimInstance::AnimNotify_AttackEnd()
{
	//애니메이션이 거의 끝나는 시점에는 콤보 공격이 불가능하고 애니메이션이 종료되길 기다려야한다.

	bAttackPlayOK = false;

	if (OnEndAbility.IsBound())
	{
		OnEndAbility.Broadcast();
	}

}

void UBaseAnimInstance::PlayAttackMontage()
{
	//공격허가가 나지 않으면 불가능
	if (!bAttackPlayOK)
	{
		return;
	}

	//현재 공격 콤보
	FName comboName = FName(*FString::Printf(TEXT("Attack%d"), ComboNumber));

	//Motage Play
	Montage_Play(BaseCombatMontage);
	Montage_JumpToSection(comboName, BaseCombatMontage);

	//애니메이션 시작할 때 공격을 추가로 더 못하게 막음
	bAttackPlayOK = false;

	//mesh를 찾고, 알맞는 Ability찾은 뒤에 Mesh에 붙임.
	auto mesh = TryGetPawnOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (IsValid(mesh))
	{
		//일단 0,0,0위치에 Spawn한 뒤에 Mesh의 소켓에 붙인다.
		 
		//기본 공격에 맞는 어빌리티 이름
		//FString abilityName = TEXT("BaseAttack_") + AbilitySuffix;

		//AOE 테스트 용도
		//FString abilityName = TEXT("AbilityAOE");
		FString abilityName = TEXT("BaseAttack_") + AbilitySuffix;


		auto ability = Cast<AAbilityBase>(UNFGameInstance::Spawn(
			abilityName, FVector(0, 0, 0), FRotator(0, 0, 0)));

		//어빌리티 초기화
		if (IsValid(ability))
		{
			//init 전에 OnStart, OnEnd를 Bind해주어야 일부 스킬 중에 즉발적으로 동작하고 사라지는 액터에 문제가 생기지 않음.

			OnStartAbility.Clear();
			OnEndAbility.Clear();
			OnStartAbility.AddDynamic(ability, &AAbilityBase::StartAbility);
			OnEndAbility.AddDynamic(ability, &AAbilityBase::EndAbility);

			ability->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			ability->InitAbility(TryGetPawnOwner(), UNFGameInstance::GetAbilityData(FName(abilityName)));
		}
	}
	
	//공격 행동 명령이 전부 끝나면 Combo++한다.
	ComboNumber++;

	if (ComboNumber > comboNumberMax)
	{
		ComboNumber = 0;
	}

}
