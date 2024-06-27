// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricLinkManager.h"

#include "Kismet/GameplayStatics.h"
#include "ElectricLinkComponent.h"

UElectricLinkManager::UElectricLinkManager()
{
}

void UElectricLinkManager::SearchAllLinks()
{
	if (!GetWorld())
	{
		return;
	}

	ElectricLinks.Empty();
	RootLinks.Empty();

	//!! : 액터가 100만개 넘으면 문제 생길 듯?
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

		if (linkComp->bRootLink)
		{
			RootLinks.Add(linkComp);
		}
	}

}

void UElectricLinkManager::LinkTest()
{
	//close set 안에 들어온 것들은 전부 activate 상태가 된다
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
	//closedSet안에 없는 것들은 모두 Deactivate한다.

	for (auto i : ElectricLinks)
	{
		if (closedSet.Contains(i))
		{
			i->Activate();
		}
		else
		{
			i->Deactivate();
		}
	}


}
