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

	if (bIsRoot)//rootüũ�� �Ǿ� ������, �� device���ʹ� ���⸦ �����ϴ� root�� �� ���̴�.
	{
		bPuzzleActive = true;
		ElectricLinkComponent->SetAsRootLink();
	}
}

void AElectricPuzzleDevice::SetPuzzleActiveByLink(bool InVal)
{
	//���� �߻��ϴ� root�� �� �Լ��� ���� bPuzzleActive�� ������ ����
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
	//Ʈ���� ���۽� �ٸ� Ʈ���ŵ� �ֵ��� ���۽�����
	//����) ���� ������ ���� ������.

	for (auto i : TriggerTargets)
	{
		auto beTriggerable = Cast<IBeTriggerable>(i);
		if (beTriggerable)
		{
			beTriggerable->BeTriggered(this, bPuzzleActive);
		}
	}
}
