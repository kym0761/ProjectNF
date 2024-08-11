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

	//tick���� �ֱ������� ���� ���� ����Ʈ ����

	ElectricEffectCounter += DeltaTime;

	if (ElectricEffectCounter >= ElectricEffectInterval)
	{
		if (bLinkActive)
		{
			for (auto i : AdjacentLinkComps)
			{
				//TODO : ��������� ���� ����Ʈ�� �����Ͽ� �����غ���
				//���ʰ��� ���� ����Ʈ�� 1���� �׸����� �ؾ���.
				// ���̵�� ? --> edge�� �����Ͽ� start�� end�� ���� ���� ����Ʈ�� �������� �ʰ� ����?

				auto niagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
					ElectricNiagaraBP,
					this,
					FName("NONE"),
					FVector(0, 0, 0),
					FRotator::ZeroRotator,
					EAttachLocation::KeepRelativeOffset,
					true);// �ð��� ������ ����Ʈ�� �˾Ƽ� Destroy�� ��.

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
	//�ֱ������� �ڽ� ��ó�� �ִ� LinkComp�� ã�´�.

	if (!bLinkActive)
	{
		return;
	}

	//TODO : Manager�� SearchAllLinks�� �޾ƿ� GetAllActorsOfClass�� ���� �ʵ��� ��������
	// Manager�� �̱������� �����ϰ� �ִ� ������ �޾ƿ����� �������� ��
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

		//AdjacentLinkComps�� TSet�̶� Unique���� �����.
		//�� �Ÿ��� �ʹ� �ָ� ���� ���� ����� �ƴ�.
		if (distance > ElectricityDistance)
		{
			AdjacentLinkComps.Remove(otherLinkComp);
		}
		else
		{
			//���� link�� ������. ���� ���� �Ǵ��� LinkManager���� �ñ��.
			AdjacentLinkComps.Add(otherLinkComp);
		}
		
	}

	//�ڽ��� ������
	AdjacentLinkComps.Remove(this);

}

void UElectricLinkComponent::ElectricLinkActivate()
{
	//LinkComponent�� ���� Active�Ѵ�.

	if (bRootLink) // root�� ��� Ȱ��ȭ�� ��ŵ
	{
		return;
	}

	if (bLinkActive)// �̹� Ȱ��ȭ ���¸� ��ŵ
	{
		return;
	}

	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive);
	
}

void UElectricLinkComponent::ElectricLinkDeactivate()
{
	//Link Component�� ��Ȱ��ȭ�Ѵ�.

	if (bRootLink) // root�� ��� Ȱ��ȭ�� ��ŵ
	{
		return;
	}

	if (!bLinkActive) //�̹� ��Ȱ��ȭ ���¸� ��ŵ
	{
		return;
	}

	bLinkActive = false;
	OnLinkActivatedChanged.Broadcast(bLinkActive);

}

void UElectricLinkComponent::SetAsRootLink()
{
	//PuzzleDevice�� ���� ���� BeginPlay()���� Root������ �� ���̴�.

	bRootLink = true;
	bLinkActive = true;
	OnLinkActivatedChanged.Broadcast(bLinkActive);
}
