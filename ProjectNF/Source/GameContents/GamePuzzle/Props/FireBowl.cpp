// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBowl.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

AFireBowl::AFireBowl()
{
	FireOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("FireOverlap"));
	FireOverlap->InitBoxExtent(FVector(64.0f, 64.0f, 64.0f));
	FireOverlap->SetupAttachment(RootComponent);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(RootComponent);
	FireEffect->bAutoActivate = false;

	bFireOn = false;
}

void AFireBowl::Combust()
{
	TurnOn();
}

void AFireBowl::Extinguish()
{
	TurnOff();
}

void AFireBowl::TurnOn()
{
	if (bFireOn == true)
	{
		return;
	}

	bFireOn = true;

	if (IsValid(FireEffect) && !FireEffect->IsActive())
	{
		FireEffect->Activate();
	}

	if (!CombustTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireBowl::OverlapCombust, 0.1f, true, 0.0f);
	}

}

void AFireBowl::TurnOff()
{
	if (bFireOn == false)
	{
		return;
	}

	bFireOn = false;

	if (IsValid(FireEffect) && FireEffect->IsActive())
	{
		FireEffect->Deactivate();
	}

	if (CombustTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}
}

void AFireBowl::OverlapCombust()
{
	if (!bFireOn)
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
		return;
	}

	TArray<AActor*> overlapActors;

	FireOverlap->GetOverlappingActors(overlapActors);
	overlapActors.Remove(this);

	for (AActor* i : overlapActors)
	{
		auto combustible = Cast<ICombustible>(i);

		if (combustible)
		{
			combustible->Combust();
		}

	}
}
