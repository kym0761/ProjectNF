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

	//TODO : linkcollision이 따로 필요할 것..

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
		
		//TODO : LinkTrigger의 Owner의 triggeractive = true함?
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
	//주기적으로 LinkComp를 찾는다.

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

	//자신은 제외함
	AdjacentLinkComps.Remove(this);

}

void UElectricLinkComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// overlap Begin되면 감지할 UElectricLinkComponent 를 추가하려고 했는데
	// 어차피 Timer로 주기적으로 감지하게 되어 BeginOverlap에서 아무 것도 안함
	// 혹시 필요할 일이 있을지도 모르니 냅둠.

	if (!IsValid(OtherActor))
	{
		return;
	}

	auto linkComp = OtherActor->FindComponentByClass<UElectricLinkComponent>();

	if (!IsValid(linkComp))
	{
		return;
	}

	//범위에 들어온 LinkComp를 인접 LinkComp에 추가함.
	AdjacentLinkComps.Add(linkComp);

}

void UElectricLinkComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//다른 LinkComp가 Overlap을 벗어나면 인접 LinkComp에서 제외함.

	if (!IsValid(OtherActor))
	{
		return;
	}

	auto linkComp = OtherActor->FindComponentByClass<UElectricLinkComponent>();

	if (!IsValid(linkComp))
	{
		return;
	}
	
	//벗어난 linkComp 제거
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

	//TODO : 인접한 Link에 전기 연결 이펙트 생성

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

	//TODO : 인접한 Link와 연결되었던 전기 연결 이펙트 제거
}
