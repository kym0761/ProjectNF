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
		//�߸��� TriggerActor
		return;
	}

	TriggerMap[key] = Val;
}

bool APuzzleActorBase::CheckTriggersHaveActivated() const
{
	if (TriggerMap.Num() == 0)
	{
		//Ʈ���� �� �� �͵��� ������ true ��ȯ
		return true;
	}

	//�۵��� �����Ѱ�? == triggermap �ȿ� bool�� false ���� ������ ����.

	for (auto pi : TriggerMap)
	{
		if (pi.Value == false)
		{
			//�Ұ���
			return false;
		}
	}

	return true;
}
