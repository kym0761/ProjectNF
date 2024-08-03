// Fill out your copyright notice in the Description page of Project Settings.


#include "GridVisualComponent.h"
#include "Defines/Data.h"
#include "DebugHelper.h"

UGridVisualComponent::UGridVisualComponent()
{
	SetCollisionProfileName(TEXT("NoCollision"));

	SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void UGridVisualComponent::DrawSingleGrid(const FVector& Location)
{
	ClearInstances();

	FTransform transform;
	transform.SetLocation(Location);
	AddInstance(transform, true);
}

void UGridVisualComponent::DrawGridVisuals(const TArray<FVector>& ToDraws)
{
	//다시 draw 해야하는지 확인함.
	{
		int32 cacheNum = LocationCache.Num();

		int32 cnt = 0;
		bool bCheck = true;
		for (auto& loc : ToDraws)
		{
			if (!LocationCache.Contains(loc))
			{
				bCheck = false;
				break;
			}

			cnt++;
		}

		if (cnt == cacheNum && bCheck) //다시 draw할 필요없음.
		{
			//Debug::Print(DEBUG_TEXT("Same"));
			return;
		}
	}
	

	LocationCache.Empty(ToDraws.Num());

	TArray<FTransform> transforms;
	for (auto& loc : ToDraws)
	{
		LocationCache.Add(loc);
		FTransform transform;
		transform.SetLocation(loc);
		transform.SetScale3D(GetComponentScale());
		transforms.Add(transform);
	}

	//다시 draw하기 위해 clear후 add
	ClearInstances();
	AddInstances(transforms, false, true); //world space?

}
