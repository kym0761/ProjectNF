// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStand.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"


AFireStand::AFireStand()
{
	PrimaryActorTick.bCanEverTick = true;

	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	SetRootComponent(Stand);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(Stand, TEXT("EffectSocket"));
	FireEffect->bAutoActivate = false;

	FireOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("FireOverlap"));
	FireOverlap->InitBoxExtent(FVector(48.0f, 48.0f, 100.0f));
	FireOverlap->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	FireOverlap->SetupAttachment(RootComponent);

}

void AFireStand::BeginPlay()
{
	Super::BeginPlay();

	//시간제한 화로대면 Widget 생성이 필요

}

void AFireStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//시간 제한 화로대면 시간 계산 필요
}

void AFireStand::Trigger_Implementation()
{
	//트리거 동작시 다른 트리거될 애들을 동작시켜줌

	for (auto i : TriggerTargets)
	{
		if (i->GetClass()->ImplementsInterface(UBeTriggerable::StaticClass()))
		{
			IBeTriggerable::Execute_BeTriggered(i);
		}
	}


}

void AFireStand::BeTriggered_Implementation()
{
	//트리거 당했을 때의 동작.. 예시) 버튼 눌러서 불이 켜짐

	bool bAllTriggerOk = true;

	for (auto i : WhoTriggerThis)
	{
		if (i->GetTriggerActive() == false)
		{
			bAllTriggerOk = false;
			break;
		}
	}

	if (bAllTriggerOk)
	{
		//TurnOn();
		ICombustible::Execute_Combust(this);
	}
	//??
}

void AFireStand::Reset_Implementation()
{
	TurnOff();
}

void AFireStand::Combust_Implementation()
{
	TurnOn();
}

void AFireStand::Extinguish_Implementation()
{
	TurnOff();
}

void AFireStand::OverlapCombust()
{
	if (!bTriggerActive)
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
		return;
	}

	//이 화로대에 불이 붙어있을 때, 근처에 닿고 있는 다른 화로대 같은 것이 있다면 그 액터를 Combust해준다.

	TArray<AActor*> overlapActors;

	FireOverlap->GetOverlappingActors(overlapActors);
	overlapActors.Remove(this);

	for (auto i : overlapActors)
	{
		if (i->GetClass()->ImplementsInterface(UCombustible::StaticClass()))
		{
			ICombustible::Execute_Combust(i);
		}
	}


}

void AFireStand::TurnOn()
{
	if (bTriggerActive == true)
	{
		return;
	}

	bTriggerActive = true;

	if ( IsValid(FireEffect) && !FireEffect->IsActive())
	{
		FireEffect->Activate();
	}

	//TODO : UI 보이기, Trigger 동작, Combust Timer 동작
	//TODO2 : TurnOff는 반대로

	//불이 켜지면서 Trigger 동작
	ITriggerable::Execute_Trigger(this);


	if (!CombustTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireStand::OverlapCombust, 1.0f, true, 0.1f);
	}
	
	
}

void AFireStand::TurnOff()
{
	if (bTriggerActive == false)
	{
		return;
	}

	bTriggerActive = false;

	if (IsValid(FireEffect) && FireEffect->IsActive())
	{
		FireEffect->Deactivate();
	}

	if (CombustTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}
	
}
