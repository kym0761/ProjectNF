// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Kismet/KismetSystemLibrary.h"

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
	/*UObject* outer = GetOuter();

	while (IsValid(outer))
	{
		GEngine->AddOnScreenDebugMessage(
			FMath::Rand(), 3.0f, FColor::Black,
			FString::Printf(TEXT("outer : %s"), *outer->GetName()));

		outer = outer->GetOuter();
	}*/

	/*
	* GameMode�� outer�� Getworld()�� �����ȴ�.
	*/

	if (GetWorld())
	{
		FVector gridToWorld = GridToWorld(Grid);
		FVector start = gridToWorld + FVector::UpVector * 10000;
		FVector end = gridToWorld + FVector::DownVector * 10000;

		FHitResult hit;

		TArray<AActor*> ignores;

		bool hitResult = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			start,
			end,
			CellSize / 3, //gridsize�� 1/2~1/3���� �����ϴ� ���� ����.
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), //������Ʈ ������ traceä�� 1
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
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					FMath::Rand(), 3.0f, FColor::Black,
					FString::Printf(TEXT("on grid : %s"), *hit.GetActor()->GetName()));
				return true;
			}
		}

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			FMath::Rand(), 3.0f, FColor::Black,
			TEXT("Getworld is nullptr"));
	}

	return false;
}