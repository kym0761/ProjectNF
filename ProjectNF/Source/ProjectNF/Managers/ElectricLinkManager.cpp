// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricLinkManager.h"

#include "Kismet/GameplayStatics.h"
#include "GamePuzzle/PuzzleActors/ElectricLink/ElectricLinkComponent.h"

#include "DebugHelper.h"

UElectricLinkManager::UElectricLinkManager()
{
}

void UElectricLinkManager::SearchAllLinks()
{
	//맵에 존재하는 모든 Electric Link Component 들을 검색한다.
	//레벨에서 최초 1번만 실행될 것이다.
	//게임 중간에 Link를 보유한 Actor가 추가된다면 이를 다시 실행해야 할 수도 있다.

	//UObject* outer = this;
	//while (IsValid(outer))
	//{
	//	Debug::Print(DEBUG_STRING(FString::Printf(TEXT("%s"),*outer->GetName())));
	//	outer = outer->GetOuter();
	//}

	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("GEngine is Invalid."));
		return;
	}

	auto world = GEngine->GetCurrentPlayWorld();

	if (!IsValid(world))
	{
		Debug::Print(DEBUG_TEXT("World is Invalid."));
		return;
	}

	ElectricLinks.Empty();
	RootLinks.Empty();

	//!! : 액터가 100만개 넘으면 약간의 문제가 생길 듯?
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(world, AActor::StaticClass(), allActors);

	for (auto i : allActors)
	{
		auto linkComp = i->FindComponentByClass<UElectricLinkComponent>();
		if (!IsValid(linkComp))
		{
			continue;
		}

		ElectricLinks.Add(linkComp);

		if (linkComp->bRootLink)
		{
			RootLinks.Add(linkComp);
		}
	}

}

void UElectricLinkManager::LinkTest()
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
			i->ElectricLinkActivate();
		}
		else
		{
			i->ElectricLinkDeactivate();
		}
	}


}

void UElectricLinkManager::InitManager()
{
	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("GEngine is Invalid."));
		return;
	}

	SearchAllLinks();


	UWorld* world = GEngine->GetCurrentPlayWorld();
	if (!IsValid(world))
	{
		Debug::Print(DEBUG_TEXT("world is invalid."));
		return;
	}


	world->GetTimerManager().SetTimer(
		ElectricLinkTimer,
		this,
		&UElectricLinkManager::LinkTest,
		1.0f,
		true,
		1.0f
	);



}
