// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSubsystem.h"
#include "DebugHelper.h"
#include "Kismet/KismetSystemLibrary.h"

UGridSubsystem::UGridSubsystem()
{
}

void UGridSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGridSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

FGrid UGridSubsystem::WorldToGrid(const FVector& WorldLocation) const
{
	FGrid grid;

	grid.X = FMath::CeilToInt32(WorldLocation.X / CellSize);
	grid.Y = FMath::CeilToInt32(WorldLocation.Y / CellSize);

	return grid;
}

FVector UGridSubsystem::GridToWorld(const FGrid& Grid) const
{
	FVector worldLocation = FVector::ZeroVector;
	worldLocation.X += Grid.X * CellSize - CellSize / 2;
	worldLocation.Y += Grid.Y * CellSize - CellSize / 2;

	return worldLocation;
}

bool UGridSubsystem::IsSomethingExistOnGrid(const FGrid& Grid) const
{
	if (!GEngine)
	{
		FMyDebug::Print(DEBUG_TEXT("GEngine is Invalid."));
	}

	// ?? : EngineSubsystem은 GetWorld()가 어떨까? -> 답 : 플레이어의 월드다.
	//GetCurrentPlayWorld()는 Outer와 상관없이 현재 게임의 World를 얻을 수 있다.
	auto world = //GEngine->GetCurrentPlayWorld();
	GetWorld();

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
			FMyDebug::Print(DEBUG_VATEXT(TEXT("on grid : %s"), *hit.GetActor()->GetName()));
			return true;
		}

	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("world is nullptr"));
	}

	return false;
}
