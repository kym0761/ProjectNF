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

	//TODO : ?

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

	//tick에서 이펙트를 주기적으로 생성한다.

	ElectricEffectCounter += DeltaTime;

	if (ElectricEffectCounter >= ElectricEffectInterval)
	{
		if (bLinkActive)
		{
			for (auto i : AdjacentLinkComps)
			{
				//TODO : 나이아가라 한 방향으로만 나오게 하기?
				//현재 양방향에서 이펙트를 쏜다.

				auto niagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
					ElectricNiagaraBP,
					this,
					FName("NONE"),
					FVector(0, 0, 0),
					FRotator::ZeroRotator,
					EAttachLocation::KeepRelativeOffset,
					true);// 주기적으로 삭제될 것

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
	

	if (!bLinkActive)
	{
		return;
	}

	//TODO : 액터 필터링 필요?
	//지금 모든 액터들을 검색하기 때문에 비효율적일 수 있음.
	//PuzzleSubsystem에서 보유한 액터들만 사용하도록 하기?

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

		//AdjacentLinkComps는 TSet이라 Unique한 값을 가진다.
		//거리를 벗어나면 인접 링크에서 제거
		if (distance > ElectricityDistance)
		{
			AdjacentLinkComps.Remove(otherLinkComp);
		}
		else
		{
			//거리 안이라면 인접 링크에서 추가한다.
			AdjacentLinkComps.Add(otherLinkComp);
		}
		
	}

	//자신은 제외한다.
	AdjacentLinkComps.Remove(this);

}

void UElectricLinkComponent::ElectricLinkActivate()
{

	if (bRootLink) // root는 이미 액티브 상태임
	{
		return;
	}

	if (bLinkActive)// 이미 액티브 상태임
	{
		return;
	}

	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive); // 액티브 상태가 변함
	
}

void UElectricLinkComponent::ElectricLinkDeactivate()
{
	
	if (bRootLink) // root는 액티브 상태 고정임
	{
		return;
	}

	if (!bLinkActive) //이미 비활성화 상태임
	{
		return;
	}

	bLinkActive = false;
	OnLinkActivatedChanged.Broadcast(bLinkActive); //액티브 상태가 변함

}

void UElectricLinkComponent::SetAsRootLink()
{
	//PuzzleDevice가 BeginPlay()에서 자신의Link컴포넌트를 Root로 만들 것이다.

	bRootLink = true;
	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive);
}
