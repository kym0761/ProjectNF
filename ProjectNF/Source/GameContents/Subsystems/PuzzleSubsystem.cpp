// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GamePuzzle/ElectricLink/ElectricLinkComponent.h"
#include "DebugHelper.h"
#include "GamePuzzle/ElectricLink/ElectricPuzzleDevice.h"

UPuzzleSubsystem::UPuzzleSubsystem()
{
}

void UPuzzleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UPuzzleSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UPuzzleSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	SearchAllLinks();

	GetWorld()->GetTimerManager().SetTimer(
		ElectricLinkTimer,
		this,
		&UPuzzleSubsystem::LinkTest,
		1.0f,
		true,
		1.0f
	);

}

void UPuzzleSubsystem::SearchAllLinks()
{
	ElectricLinks.Empty();
	RootLinks.Empty();

	//!! : 액터가 100만개 넘으면 약간의 문제가 생길 듯?
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	for (auto i : allActors)
	{
		auto linkComp = i->FindComponentByClass<UElectricLinkComponent>();
		if (!IsValid(linkComp))
		{
			continue;
		}

		ElectricLinks.Add(linkComp);

		auto electricDevice = Cast<AElectricPuzzleDevice>(i);
		if (IsValid(electricDevice) && electricDevice->bIsRoot)
		{
			RootLinks.Add(linkComp);
			linkComp->SetAsRootLink();
		}
	}

	//FMyDebug::Print(DEBUG_VATEXT(TEXT("Actor Num : %d"), allActors.Num()));
	//FMyDebug::Print(DEBUG_VATEXT(TEXT("Electric Links Num : %d") , ElectricLinks.Num()));
	//FMyDebug::Print(DEBUG_VATEXT(TEXT("RootLinks Num : %d"), RootLinks.Num()));
}

void UPuzzleSubsystem::LinkTest()
{
	//closeSet 안에 들어온 것들은 전부 activate 상태가 된다
	TSet<TObjectPtr<UElectricLinkComponent>> closedSet;

	for (auto root : RootLinks)
	{
		TQueue<TObjectPtr<UElectricLinkComponent>> linkCompQueue;

		linkCompQueue.Enqueue(root);

		while (!linkCompQueue.IsEmpty())
		{
			TObjectPtr<UElectricLinkComponent> popResult = *linkCompQueue.Peek();
			linkCompQueue.Pop();

			closedSet.Add(popResult);

			if (!IsValid(popResult))
			{
				continue;
			}

			for (auto i : popResult->AdjacentLinkComps)
			{
				if (closedSet.Contains(i))
				{
					continue;
				}

				linkCompQueue.Enqueue(i);
			}
		}
	}

	//closedSet 안에 있는 모든 것들을 Activate한다.
	//closedSet 안에 없는 것들은 모두 Deactivate한다.
	for (auto i : ElectricLinks)
	{
		if (closedSet.Contains(i))
		{
			//FMyDebug::Print(DEBUG_TEXT("Active."));
			i->ElectricLinkActivate();
		}
		else
		{
			//FMyDebug::Print(DEBUG_TEXT("de-Active."));
			i->ElectricLinkDeactivate();
		}
	}

}
