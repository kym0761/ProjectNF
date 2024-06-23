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

	//�ð����� ȭ�δ�� Widget ������ �ʿ�

}

void AFireStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�ð� ���� ȭ�δ�� �ð� ��� �ʿ�
}

void AFireStand::Trigger_Implementation()
{
	//Ʈ���� ���۽� �ٸ� Ʈ���ŵ� �ֵ��� ���۽�����

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
	//Ʈ���� ������ ���� ����.. ����) ��ư ������ ���� ����

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

	//�� ȭ�δ뿡 ���� �پ����� ��, ��ó�� ��� �ִ� �ٸ� ȭ�δ� ���� ���� �ִٸ� �� ���͸� Combust���ش�.

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

	//TODO : UI ���̱�, Trigger ����, Combust Timer ����
	//TODO2 : TurnOff�� �ݴ��

	//���� �����鼭 Trigger ����
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
