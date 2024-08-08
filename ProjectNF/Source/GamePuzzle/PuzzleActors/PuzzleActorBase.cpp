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

	//TriggerTargets가 변경된다면, 이전 TriggerTargets의 값을 저장함.
	//PostEditChangeProperty를 통해 TriggerTargets 변화에 따라
	//triggerMap을 만들어준다.
	if (PropertyAboutToChange->GetName() == GET_MEMBER_NAME_CHECKED(APuzzleActorBase, TriggerTargets))
	{
		FMyDebug::Print(DEBUG_TEXT("You Revised TriggerTarget!"));
		PrevTriggerTargets = TriggerTargets;
	}

}

void APuzzleActorBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty IN %s"), *this->GetName());

	//prevTriggerTargets과 triggerTargets의 변화에 따라
	//triggerTargets에 새로 들어온 Actor에 접근해 TriggerMap 세팅
	//prevTriggerTargets에 있었지만 현재 triggerTargets에서는 없어진 Actor에는 TriggerMap에서 제거한다.
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(APuzzleActorBase, TriggerTargets))
	{

		//1. 현재 array에 있는 액터가 prev_array에 없었다면, triggerMap에 추가
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

		//2. prev_array에 있던 액터가 현재 array에 없다면, triggerMap에서 제거
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

#if WITH_EDITOR

void APuzzleActorBase::AddToTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToAdd)
{
	//에디터에서 추가 기능
	TriggerMap.Add(PuzzleActorToAdd->GetName(), false);
}

void APuzzleActorBase::RemoveFromTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToRemove)
{
	//에디터에서 제거 기능
	TriggerMap.Remove(PuzzleActorToRemove->GetName());
}

#endif // WITH_EDITOR