// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricLinkComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ElectricLinkComponent.h"

UElectricLinkComponent::UElectricLinkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//TODO : linkcollision이 따로 필요할 것..

	bRootLink = false;
	bLinkActive = false;

}

void UElectricLinkComponent::BeginPlay()
{
	Super::BeginPlay();


	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LinkJobTimer, this, &UElectricLinkComponent::LinkJob, LinkJobInterval, true);
	}

}

void UElectricLinkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//tick에서 주기적으로 전기 연결 이펙트 생성

	ElectricEffectCounter += DeltaTime;

	if (ElectricEffectCounter >= ElectricEffectInterval)
	{
		if (bLinkActive)
		{
			for (auto i : AdjacentLinkComps)
			{
				//TODO : 양방향으로 전기 이펙트를 생성하여 난잡해보임
				//양쪽간에 전기 이펙트를 1개만 그리도록 해야함.
				// 아이디어 ? --> edge로 가정하여 start와 end가 같은 전기 이펙트를 생성하지 않게 방지?

				auto niagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
					ElectricNiagaraBP,
					this,
					FName("NONE"),
					FVector(0, 0, 0),
					FRotator::ZeroRotator,
					EAttachLocation::KeepRelativeOffset,
					true);// 시간이 지나면 이펙트가 알아서 Destroy될 것.

				if (!IsValid(niagaraComp))
				{
					continue;
				}

				niagaraComp->SetVariableVec3(TEXT("StartPos"), GetComponentLocation());
				niagaraComp->SetVariableVec3(TEXT("EndPos"), i->GetComponentLocation());
			}
		}

		ElectricEffectCounter = 0.0f;
	}

}

void UElectricLinkComponent::LinkJob()
{
	//주기적으로 자신 근처에 있는 LinkComp를 찾는다.

	if (!bLinkActive)
	{
		return;
	}

	//TODO : Manager에 SearchAllLinks를 받아와 GetAllActorsOfClass를 하지 않도록 만들어야함
	// Manager를 싱글톤으로 관리하고 있는 정보를 받아오도록 만들어야할 듯
	TArray<AActor*> outActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), outActor);

	for (auto i : outActor)
	{
		auto otherLinkComp = i->FindComponentByClass<UElectricLinkComponent>();

		if (!IsValid(otherLinkComp))
		{
			continue;
		}

		float distance = FVector::Distance(this->GetComponentLocation(), otherLinkComp->GetComponentLocation());

		//AdjacentLinkComps는 TSet이라서 Unique함이 보장됨.
		//두 거리가 너무 멀면 전기 연결 대상이 아님.
		if (distance > ElectricityDistance)
		{
			AdjacentLinkComps.Remove(otherLinkComp);
		}
		else
		{
			//인접 link에 저장함. 전기 연결 판단은 LinkManager에게 맡긴다.
			AdjacentLinkComps.Add(otherLinkComp);
		}
		
	}

	//자신은 제외함
	AdjacentLinkComps.Remove(this);

}

void UElectricLinkComponent::ElectricLinkActivate()
{
	//LinkComponent를 최초 Active한다.

	if (bRootLink) // root는 상시 활성화라 스킵
	{
		return;
	}

	if (bLinkActive)// 이미 활성화 상태면 스킵
	{
		return;
	}

	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive);
	
}

void UElectricLinkComponent::ElectricLinkDeactivate()
{
	//Link Component를 비활성화한다.

	if (bRootLink) // root는 상시 활성화라 스킵
	{
		return;
	}

	if (!bLinkActive) //이미 비활성화 상태면 스킵
	{
		return;
	}

	bLinkActive = false;
	OnLinkActivatedChanged.Broadcast(bLinkActive);

}

void UElectricLinkComponent::SetAsRootLink()
{
	//PuzzleDevice의 값에 따라 BeginPlay()에서 Root세팅이 될 것이다.

	bRootLink = true;
	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive);
}
