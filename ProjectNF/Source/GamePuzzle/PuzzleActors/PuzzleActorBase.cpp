// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleActorBase.h"

// Sets default values
APuzzleActorBase::APuzzleActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitTriggerMap();
}

// Called every frame
void APuzzleActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleActorBase::InitTriggerMap()
{
	for (auto i : TriggerTargets)
	{
		i->TriggerMap.Add(GetName(), false);
	}

}

void APuzzleActorBase::SendTriggerParams(TObjectPtr<APuzzleActorBase> TriggerActor, bool Val)
{
	FString key = TriggerActor->GetName();

	if (!TriggerMap.Contains(key))
	{
		//잘못된 TriggerActor
		return;
	}

	TriggerMap[key] = Val;
}

bool APuzzleActorBase::CheckTriggersHaveActivated() const
{
	if (TriggerMap.Num() == 0)
	{
		//트리거 해 줄 것들이 없으면 true 반환
		return true;
	}

	//작동이 가능한가? == triggermap 안에 bool이 false 값이 없으면 가능.

	for (auto pi : TriggerMap)
	{
		if (pi.Value == false)
		{
			//불가능
			return false;
		}
	}

	return true;
}
