// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricPuzzleDevice.h"
#include "Components/StaticMeshComponent.h"
#include "ElectricLinkComponent.h"

AElectricPuzzleDevice::AElectricPuzzleDevice()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	ElectricLinkComponent = CreateDefaultSubobject<UElectricLinkComponent>(TEXT("ElectricLink"));
	ElectricLinkComponent->SetupAttachment(RootComponent);
}

void AElectricPuzzleDevice::BeginPlay()
{
	Super::BeginPlay();

	ElectricLinkComponent->OnLinkActivatedChanged.AddDynamic(this, &AElectricPuzzleDevice::SetPuzzleActiveByLink);

	if (bIsRoot)//root체크가 되어 있으면, 이 device액터는 전기를 생산하는 root가 될 것이다.
	{
		bPuzzleActive = true;
		ElectricLinkComponent->SetAsRootLink();
	}
}

void AElectricPuzzleDevice::SetPuzzleActiveByLink(bool InVal)
{
	//전기 발생하는 root는 이 함수에 의해 bPuzzleActive가 변하지 않음
	if (!bIsRoot)
	{
		bPuzzleActive = InVal;
	}
	Trigger();
}

void AElectricPuzzleDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElectricPuzzleDevice::Trigger()
{
	//트리거 동작시 다른 트리거될 애들을 동작시켜줌
	//예시) 불이 붙으면 문이 열린다.

	for (auto i : TriggerTargets)
	{
		auto beTriggerable = Cast<IBeTriggerable>(i);
		if (beTriggerable)
		{
			beTriggerable->BeTriggered(this, bPuzzleActive);
		}
	}
}
