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

void AAbilityCapsuleOverlap::InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal)
{
	if (!IsValid(AbilityOwnerVal))
	{
		FMyDebug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;
	AbilityData = AbilityDataVal;
	//이 어빌리티에 AbilityTarget은 필요없음.
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

	if (OtherActor == AbilityOwner)
	{
		return;
	}

	FMyDebug::Print(DEBUG_VATEXT(TEXT("Overlapped By Ability : %s"), *OtherActor->GetName()));

	if (RequestSpawnNiagara.IsBound())
	{
		RequestSpawnNiagara.Execute(AbilityData.AbilityNiagara, (OtherActor->GetActorLocation() + GetActorLocation())/ 2, FRotator::ZeroRotator);
	}


	//TODO : BeginOverlap 된 지점에 이펙트를 보이게 하기(현재 그냥 OtherActor 위치에 이펙트 나옴.) -> Overlap은 Hit Event가 안나옴
	//TODO : 오버랩된 적에게 피해 주기

}
