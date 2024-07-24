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
	//�ʿ� �����ϴ� ��� Electric Link Component ���� �˻��Ѵ�.
	//���� ���� �� ���� 1���� ����� ���̴�.
	//���� �߰��� Link�� ������ Actor�� �߰��ȴٸ� �̸� �ٽ� �����ؾ� �� ���� �ִ�.

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
	//closeSet �ȿ� ���� �͵��� ���� activate ���°� �ȴ�
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
	//closedSet �ȿ� ���� �͵��� ��� Deactivate�Ѵ�.
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

void UElectricLinkManager::ManagerInit()
{
	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("GEngine is Invalid."));
	}

	SearchAllLinks();


	auto world = GEngine->GetCurrentPlayWorld();

	world->GetTimerManager().SetTimer(
		ElectricLinkTimer,
		this,
		&UElectricLinkManager::LinkTest,
		1.0f,
		true,
		1.0f
	);



}
