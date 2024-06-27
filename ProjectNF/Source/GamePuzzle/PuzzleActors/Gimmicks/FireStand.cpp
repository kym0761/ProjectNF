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


	fireCount += DeltaTime;
	if (fireCount >= FireInterval)
	{
		if (bFireOn)
		{
			if (!FireEffect->IsActive())
			{
				FireEffect->Activate();
			}
		}
		else
		{
			if (FireEffect->IsActive())
			{
				FireEffect->Deactivate(); //de-active�� ����Ʈ emitter�� Ȱ���� �Ϸ�ɶ� �Ͼ�� ��� active & deactive ��ȯ�� ���� ����.
			}
		}

		fireCount = 0.0f;
	}


	//TODO : �ð� ���� ȭ�δ�� �ð� ��� �ʿ�

}

void AFireStand::Trigger()
{
	//Ʈ���� ���۽� �ٸ� Ʈ���ŵ� �ֵ��� ���۽�����
	//����) ���� ������ ���� ������.

	for (auto i : TriggerTargets)
	{
		auto beTriggerable = Cast<IBeTriggerable>(i);
		if (beTriggerable)
		{
			beTriggerable->BeTriggered(this, bFireOn);
		}
	}

}

void AFireStand::BeTriggered(TObjectPtr<class APuzzleActorBase> TriggerActor, bool TriggerValue)
{
	//Ʈ���� ������ ���� ����.. ����) ��ư ������ ���� ����
	//FireStand�� ���� ������ �ٿ��� BeTriggered�� ��ġ�� �ʰ� ���� ���� ���� ����.

	SendTriggerParams(TriggerActor, TriggerValue);

	bool bOk = CheckTriggersHaveActivated();

	if (bOk)
	{
		Combust();
	}

	//�� �Ұ� �ִ���?
}

void AFireStand::Reset()
{
	TurnOff();
}

void AFireStand::Combust()
{
	TurnOn();
}

void AFireStand::Extinguish()
{
	TurnOff();
}

void AFireStand::OverlapCombust()
{
	//�� FireStand ���� �پ����� ��, ��ó�� ��� �ִ� �ٸ� Combustible ��ü�� �ִٸ� �� ���͸� Combust���ش�.

	TArray<AActor*> overlapActors;

	FireOverlap->GetOverlappingActors(overlapActors);
	overlapActors.Remove(this);

	for (auto i : overlapActors)
	{
		auto combustible = Cast<ICombustible>(i);
		if (combustible)
		{
			combustible->Combust();
		}
	}

}

void AFireStand::TurnOn()
{
	if (bFireOn == true)
	{
		return;
	}

	bFireOn = true;

	//TODO : �� ���� �ð� UI ���̱�
	//TODO2 : TurnOff�� �ݴ��

	//���� �����鼭 Trigger ����
	Trigger();

	if (!CombustTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireStand::OverlapCombust, 1.0f, true, 0.1f);
	}
	
}

void AFireStand::TurnOff()
{
	if (bFireOn == false)
	{
		return;
	}

	bFireOn = false;

	//TODO: UI �Ⱥ��̰� �ϱ�
	//turnOn ����

	//���� �����鼭 Trigger �������� Deactive �˸�
	Trigger();
	
	if (CombustTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}
	
}
