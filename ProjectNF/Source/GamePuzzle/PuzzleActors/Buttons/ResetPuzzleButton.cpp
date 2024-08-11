// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPuzzleButton.h"
#include "Components/SphereComponent.h"

AResetPuzzleButton::AResetPuzzleButton()
{
}

void AResetPuzzleButton::BeginPlay()
{
	//리셋버튼은 AActor의 기본 BeginPlay()가 동작하도록 해야함.

	Super::Super::Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonEndOverlap);
}

void AResetPuzzleButton::Tick(float DeltaTime)
{
	//리셋버튼은 AActor의 기본 Tick()이 동작하도록 해야함.
	Super::Super::Super::Tick(DeltaTime);

	if (bButtonActive)
	{
		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonDownPos, DeltaTime * 10);

		//버튼 눌리기
		ButtonMesh->SetRelativeLocation(lerpVal);
	}
	else
	{
		//버튼 다시 올라오기
		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonUpPos, DeltaTime * 10);

		ButtonMesh->SetRelativeLocation(lerpVal);
	}
}

void AResetPuzzleButton::ButtonUp()
{
	bButtonActive = false;
	//리셋 버튼은 올라왔을 때 누군가를 다시 트리거해줄 필요가 없음.
}

void AResetPuzzleButton::Trigger()
{
	for (auto i : TriggerTargets)
	{
		auto resetable = Cast<IResetable>(i);

		if (resetable)
		{
			resetable->Reset();
		}
	}
}
