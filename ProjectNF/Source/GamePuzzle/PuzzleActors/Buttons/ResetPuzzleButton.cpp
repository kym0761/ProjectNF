// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPuzzleButton.h"
#include "Components/SphereComponent.h"

AResetPuzzleButton::AResetPuzzleButton()
{
}

void AResetPuzzleButton::BeginPlay()
{
	//APuzzleActorBase�� �ִ� BeginPlay()�� �ٸ� Puzzle ���͵��� WhoTriggerThis�� ����ϴ� ������ ��.
	//���� ResetButton�� �� ������ �ϰ� �ȴٸ�, Trigger ����� ResetButton�� Activate ������ ���� ���� ������ �Ϸ��� ����� �Ͼ.
	//�׷��Ƿ� AActor::BeginPlay()�� �����ϰ� �ؾ��ϹǷ� ���Ӱ� Sphere �̺�Ʈ�� �����.

	Super::Super::Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AResetPuzzleButton::OnButtonEndOverlap);
}

void AResetPuzzleButton::Tick(float DeltaTime)
{
	//Tick()�� BeginPlay()�� ����� ������ AActor::Tick()�� �����ϰ� ��.
	Super::Super::Super::Tick(DeltaTime);

	if (bButtonActive)
	{
		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonDownPos, DeltaTime * 10);

		//ButtonMesh�� õõ�� �Ʒ���?
		ButtonMesh->SetRelativeLocation(lerpVal);
	}
	else
	{
		//ButtonMesh�� õõ�� ����?

		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonUpPos, DeltaTime * 10);

		ButtonMesh->SetRelativeLocation(lerpVal);
	}
}

void AResetPuzzleButton::ButtonUp()
{
	bButtonActive = false;
	//reset puzzle�� who trigger me? �� ���Ե��� �����Ƿ� trigger�� �ٽ� �θ� �ʿ� ����.
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
