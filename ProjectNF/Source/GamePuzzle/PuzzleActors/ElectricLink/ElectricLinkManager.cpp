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

	//!! : ���Ͱ� 100���� ������ ���� ���� ��?
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
	//close set �ȿ� ���� �͵��� ���� activate ���°� �ȴ�
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

	//closedSet �ȿ� �ִ� ��� �͵��� Activate�Ѵ�.
	//closedSet�ȿ� ���� �͵��� ��� Deactivate�Ѵ�.

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
