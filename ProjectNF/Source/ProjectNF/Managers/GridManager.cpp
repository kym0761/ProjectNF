// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DebugHelper.h"

UGridManager::UGridManager()
{

}

FGrid UGridManager::WorldToGrid(const FVector& WorldLocation) const
{
	FGrid grid;

	grid.X = FMath::CeilToInt32(WorldLocation.X / CellSize);
	grid.Y = FMath::CeilToInt32(WorldLocation.Y / CellSize);

	return grid;
}

FVector UGridManager::GridToWorld(const FGrid& Grid) const
{
	FVector worldLocation = FVector::ZeroVector;
	worldLocation.X += Grid.X * CellSize - CellSize / 2;
	worldLocation.Y += Grid.Y * CellSize - CellSize / 2;

	return worldLocation;
}

bool UGridManager::IsSomethingExistOnGrid(const FGrid& Grid) const
{
	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("GEngine is Invalid."));
	}
	
	//GetCurrentPlayWorld()는 Outer와 상관없이 현재 게임의 World를 얻을 수 있다.
	auto world = GEngine->GetCurrentPlayWorld();

	if (IsValid(world))
	{
		FVector gridToWorld = GridToWorld(Grid);
		FVector start = gridToWorld + FVector::UpVector * 10000;
		FVector end = gridToWorld + FVector::DownVector * 10000;

		FHitResult hit;

		TArray<AActor*> ignores;

		bool hitResult = UKismetSystemLibrary::SphereTraceSingle(
			world,
			start,
			end,
			CellSize / 3, //gridsize의 1/2~1/3으로 세팅하는 것이 좋다.
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), //프로젝트 세팅의 trace채널 1
			false,
			ignores,
			EDrawDebugTrace::ForDuration,
			hit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			3.0f
		);

		if (hitResult)
		{
			Debug::Print(FString::Printf(TEXT("on grid : %s"), *hit.GetActor()->GetName()));
			return true;
		}

	}
	else
	{
		Debug::Print(DEBUG_TEXT("world is nullptr"));
	}

	return false;
}

void UGridManager::InitManager()
{
	//?
}
