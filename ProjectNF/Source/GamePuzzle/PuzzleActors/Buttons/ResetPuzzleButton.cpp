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

	if (bTriggerActive)
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
