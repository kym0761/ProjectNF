// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStand.h"
#include "Components/StaticMeshComponent.h"
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
				FireEffect->Deactivate(); //de-active는 이펙트 emitter가 활동이 완료될때 일어나서 즉시 active & deactive 전환이 되지 않음.
			}
		}

		fireCount = 0.0f;
	}


	//TODO : 시간 제한 화로대면 시간 계산 필요

}

void AFireStand::Trigger()
{
	//트리거 동작시 다른 트리거될 애들을 동작시켜줌
	//예시) 불이 붙으면 문이 열린다.

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
	//트리거 당했을 때의 동작.. 예시) 버튼 눌러서 불이 켜짐
	//FireStand는 불을 강제로 붙여서 BeTriggered를 거치지 않고도 불을 붙일 수도 있음.

	SendTriggerParams(TriggerActor, TriggerValue);

	bool bOk = CheckTriggersHaveActivated();

	if (bOk)
	{
		Combust();
	}

	//더 할게 있는지?
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
	//이 FireStand 불이 붙어있을 때, 근처에 닿고 있는 다른 Combustible 객체가 있다면 그 액터를 Combust해준다.

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

	//TODO : 불 제한 시간 UI 보이기
	//TODO2 : TurnOff는 반대로

	//불이 켜지면서 Trigger 동작
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

	//TODO: UI 안보이게 하기
	//turnOn 참고

	//불이 꺼지면서 Trigger 동작으로 Deactive 알림
	Trigger();
	
	if (CombustTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}
	
}
