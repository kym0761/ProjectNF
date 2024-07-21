// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleActorBase.h"
#include "DebugHelper.h"

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

}

#if WITH_EDITOR

void APuzzleActorBase::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);

	//UE_LOG(LogTemp, Warning, TEXT("PreEditChange"));

	//TriggerTargets�� ����ȴٸ�, ���� TriggerTargets�� ���� ������.
	//PostEditChangeProperty�� ���� TriggerTargets ��ȭ�� ����
	//triggerMap�� ������ش�.
	if (PropertyAboutToChange->GetName() == GET_MEMBER_NAME_CHECKED(APuzzleActorBase, TriggerTargets))
	{
		Debug::Print(DEBUG_TEXT("You Revised TriggerTarget!"));
		PrevTriggerTargets = TriggerTargets;
	}

}

void APuzzleActorBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty IN %s"), *this->GetName());

	//prevTriggerTargets�� triggerTargets�� ��ȭ�� ����
	//triggerTargets�� ���� ���� Actor�� ������ TriggerMap ����
	//prevTriggerTargets�� �־����� ���� triggerTargets������ ������ Actor���� TriggerMap���� �����Ѵ�.
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(APuzzleActorBase, TriggerTargets))
	{

		//1. ���� array�� �ִ� ���Ͱ� prev_array�� �����ٸ�, triggerMap�� �߰�
		for (auto i : TriggerTargets)
		{
			if (!IsValid(i))
			{
				continue;
			}

			if (PrevTriggerTargets.Contains(i))
			{
				continue;
			}

			i->AddToTriggerMap(this);
		}

		//2. prev_array�� �ִ� ���Ͱ� ���� array�� ���ٸ�, triggerMap���� ����
		for (auto i : PrevTriggerTargets)
		{
			if (!IsValid(i))
			{
				continue;
			}

			if (TriggerTargets.Contains(i))
			{
				continue;
			}
			i->RemoveFromTriggerMap(this);
		}

	}

}

#endif // WITH_EDITOR

// Called every frame
void APuzzleActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

#if WITH_EDITOR

void APuzzleActorBase::AddToTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToAdd)
{
	//�����Ϳ��� �߰� ���
	TriggerMap.Add(PuzzleActorToAdd->GetName(), false);
}

void APuzzleActorBase::RemoveFromTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToRemove)
{
	//�����Ϳ��� ���� ���
	TriggerMap.Remove(PuzzleActorToRemove->GetName());
}

#endif // WITH_EDITOR