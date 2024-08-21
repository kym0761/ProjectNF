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

	////이 부분은 PuzzleSubsystem으로 옮김. 필요없어지면 삭제
	//if (bIsRoot)//루트면 전기를 생성한다고 생각하자. link컴포넌트도 루트로 지정한다.
	//{
	//	bPuzzleActive = true;
	//	ElectricLinkComponent->SetAsRootLink();
	//}
}

void AElectricPuzzleDevice::SetPuzzleActiveByLink(bool InVal)
{
	//전기를 받으면 트리거한다.

	if (!bIsRoot) //루트가 아닐때만 값이 변할 수 있다.
	{
		bPuzzleActive = InVal;
	}
	Trigger(); //액티브 상태일때 액티브 트리거 , 디액티브 상태일땐 디액티브 트리거가 됨.
}

void AElectricPuzzleDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElectricPuzzleDevice::Trigger()
{
	//트리거 가능한 대상을 전부 트리거한다.

	//활성화일 때 true로 트리거한다.
	//비활성화 상태일 때 false로 트리거한다.

	for (auto i : TriggerTargets)
	{
		auto beTriggerable = Cast<IBeTriggerable>(i);
		if (beTriggerable)
		{
			beTriggerable->BeTriggered(this, bPuzzleActive);
		}
	}
}
