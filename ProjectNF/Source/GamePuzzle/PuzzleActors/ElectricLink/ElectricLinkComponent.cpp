// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricLinkComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

UElectricLinkComponent::UElectricLinkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//TODO : linkcollision�� ���� �ʿ��� ��..

	bRootLink = false;
	bLinkActivated = false;

	InitSphereRadius(750.0f);

	ShapeColor = FColor::Blue;
}

void UElectricLinkComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bRootLink)
	{
		bLinkActivated = true;
		
		//TODO : LinkTrigger�� Owner�� triggeractive = true��?
	}

	OnComponentBeginOverlap.AddDynamic(this, &UElectricLinkComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UElectricLinkComponent::OnEndOverlap);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LinkJobTimer, this, &UElectricLinkComponent::LinkJob, 0.5f, true);
	}

}

void UElectricLinkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//?
}

void UElectricLinkComponent::LinkJob()
{
	//�ֱ������� LinkComp�� ã�´�.

	if (!bLinkActivated)
	{
		return;
	}

	TArray<AActor*> overlapActors;
	GetOverlappingActors(overlapActors);

	for (auto i : overlapActors)
	{
		auto otherLinkComp = i->FindComponentByClass<UElectricLinkComponent>();

		if (!IsValid(otherLinkComp))
		{
			continue;
		}

		AdjacentLinkComps.Add(otherLinkComp);
	}

	//�ڽ��� ������
	AdjacentLinkComps.Remove(this);

}

void UElectricLinkComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// overlap Begin�Ǹ� ������ UElectricLinkComponent �� �߰��Ϸ��� �ߴµ�
	// ������ Timer�� �ֱ������� �����ϰ� �Ǿ� BeginOverlap���� �ƹ� �͵� ����
	// Ȥ�� �ʿ��� ���� �������� �𸣴� ����.

	if (!IsValid(OtherActor))
	{
		return;
	}

	auto linkComp = OtherActor->FindComponentByClass<UElectricLinkComponent>();

	if (!IsValid(linkComp))
	{
		return;
	}

	//������ ���� LinkComp�� ���� LinkComp�� �߰���.
	AdjacentLinkComps.Add(linkComp);

}

void UElectricLinkComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//�ٸ� LinkComp�� Overlap�� ����� ���� LinkComp���� ������.

	if (!IsValid(OtherActor))
	{
		return;
	}

	auto linkComp = OtherActor->FindComponentByClass<UElectricLinkComponent>();

	if (!IsValid(linkComp))
	{
		return;
	}
	
	//��� linkComp ����
	if (AdjacentLinkComps.Contains(linkComp))
	{
		AdjacentLinkComps.Remove(linkComp);
	}

}

void UElectricLinkComponent::ElectricLinkActivate()
{
	if (bRootLink)
	{
		return;
	}

	if (bLinkActivated)
	{
		return;
	}

	bLinkActivated = true;

	//TODO : ������ Link�� ���� ���� ����Ʈ ����

	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() );

	for (auto i : AdjacentLinkComps)
	{
		auto niagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(ElectricNiagaraBP, this, FName("NONE"), FVector(0, 0, 0), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
		niagaraComp->SetNiagaraVariableVec3(TEXT("EndPos"), GetComponentLocation());
	}

	
}

void UElectricLinkComponent::ElectricLinkDeactivate()
{
	if (bRootLink)
	{
		return;
	}

	if (!bLinkActivated)
	{
		return;
	}

	bLinkActivated = false;

	//TODO : ������ Link�� ����Ǿ��� ���� ���� ����Ʈ ����
}
