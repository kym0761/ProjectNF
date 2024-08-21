// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAOE.h"
#include "Components/SphereComponent.h"
#include "DebugHelper.h"

AAbilityAOE::AAbilityAOE()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(150.0f);
	Sphere->SetupAttachment(RootComponent);
}

void AAbilityAOE::InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal)
{
	if (!IsValid(AbilityOwnerVal))
	{
		FMyDebug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;
	AbilityData = AbilityDataVal;
	//이 어빌리티는 Target을 설정할 필요가 없음.
}

void AAbilityAOE::StartAbility_Implementation()
{
	//AOE 공격 시작하면 사용자로부터 떨어짐.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	TArray<AActor*> overlappedActors;
	Sphere->GetOverlappingActors(overlappedActors);

	for (auto i : overlappedActors)
	{
		FMyDebug::Print(DEBUG_VATEXT(TEXT("Overlapped By AOE : %s"), *i->GetName()));
		//TODO : overlap된 액터에 피해주기
	}

	//EffectName에 맞는 나이아가라를 이 어빌리티 위치에 생성

	if (RequestSpawnNiagara.IsBound())
	{
		RequestSpawnNiagara.Execute(AbilityData.AbilityNiagara, GetActorLocation(), FRotator::ZeroRotator);
	}

	//EndAbility();
}

void AAbilityAOE::EndAbility_Implementation()
{
	Destroy();
}
