// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPuzzleButton.h"
#include "Components/SphereComponent.h"

AResetPuzzleButton::AResetPuzzleButton()
{
}

void AResetPuzzleButton::BeginPlay()
{
	//APuzzleActorBase에 있는 BeginPlay()는 다른 Puzzle 액터들의 WhoTriggerThis를 등록하는 역할을 함.
	//만약 ResetButton이 그 동작을 하게 된다면, Trigger 대상이 ResetButton의 Activate 변수의 값에 따라 동작을 하려는 모순이 일어남.
	//그러므로 AActor::BeginPlay()를 동작하게 해야하므로 새롭게 Sphere 이벤트를 등록함.

	Super::Super::Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonEndOverlap);
}

void AResetPuzzleButton::Tick(float DeltaTime)
{
	//Tick()도 BeginPlay()와 비슷한 이유로 AActor::Tick()을 동작하게 함.
	Super::Super::Super::Tick(DeltaTime);

	if (bTriggerActive)
	{
		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonDownPos, DeltaTime * 10);

		//ButtonMesh를 천천히 아래로?
		ButtonMesh->SetRelativeLocation(lerpVal);
	}
	else
	{
		//ButtonMesh를 천천히 위로?

		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonUpPos, DeltaTime * 10);

		ButtonMesh->SetRelativeLocation(lerpVal);
	}
}

void AResetPuzzleButton::ButtonUp()
{
	bTriggerActive = false;
}

void AResetPuzzleButton::Trigger_Implementation()
{
	for (auto i : TriggerTargets)
	{
		if (i->GetClass()->ImplementsInterface(UResetable::StaticClass()))
		{
			IResetable::Execute_Reset(i);
		}
	}
}
