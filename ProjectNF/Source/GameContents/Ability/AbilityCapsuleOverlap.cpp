// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCapsuleOverlap.h"
#include "DebugHelper.h"
#include "Components/CapsuleComponent.h"
AAbilityCapsuleOverlap::AAbilityCapsuleOverlap()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Capsule->SetupAttachment(GetRootComponent());
	Capsule->InitCapsuleSize(30, 60);
	Capsule->SetRelativeLocation(FVector(0, 0, 60));

	SetActorEnableCollision(false);
}

void AAbilityCapsuleOverlap::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AAbilityCapsuleOverlap::OnBeginOverlap);
}

void AAbilityCapsuleOverlap::InitAbility_Implementation(AActor* AbilityOwnerVal)
{
	if (!IsValid(AbilityOwnerVal))
	{
		Debug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;

	//TODO : 플레이어가 공격 기능에 맞는 애니메이션을 작동시키고, 이 어빌리티를 무기에 붙여 notify에 맞춰 오버랩 가동한다.

}

void AAbilityCapsuleOverlap::StartAbility_Implementation()
{
	SetActorEnableCollision(true);

}

void AAbilityCapsuleOverlap::EndAbility_Implementation()
{
	Destroy();
}

void AAbilityCapsuleOverlap::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	Debug::Print(DEBUG_VATEXT(TEXT("Overlapped By Ability : %s"), *OtherActor->GetName()));
}
