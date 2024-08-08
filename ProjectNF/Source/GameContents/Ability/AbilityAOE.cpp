// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityAOE.h"
#include "Components/SphereComponent.h"
#include "DebugHelper.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"

AAbilityAOE::AAbilityAOE()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(150.0f);
	Sphere->SetupAttachment(RootComponent);
}

void AAbilityAOE::InitAbility_Implementation(AActor* AbilityOwnerVal)
{
	if (!IsValid(AbilityOwnerVal))
	{
		FMyDebug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));

		//Debug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;

	//TODO : 스킬 Owner의 montage를 실행하고 notify로 StartAbility를 실행한다.
}

void AAbilityAOE::StartAbility_Implementation()
{
	//AOE 공격 시작하면 사용자로부터 떨어짐.
	AttachToActor(GetParentActor(),FAttachmentTransformRules::KeepWorldTransform);

	TArray<AActor*> overlappedActors;
	Sphere->GetOverlappingActors(overlappedActors);

	for (auto i : overlappedActors)
	{
		FMyDebug::Print(DEBUG_VATEXT(TEXT("Overlapped By AOE : %s"), *i->GetName()));
	}

	UNFGameInstance::GetObjectManager()->SpawnNiagaraSystem(EffectName, GetActorLocation());
}

void AAbilityAOE::EndAbility_Implementation()
{

	Destroy();
}
