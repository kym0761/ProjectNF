// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfoSubsystem.h"

#include "DebugHelper.h"
#include "GameFarm/FarmlandTile.h"
#include "Subsystems/GridSubsystem.h"

UGameInfoSubsystem::UGameInfoSubsystem()
{
	GameLanguage = ELanguage::English;
}

void UGameInfoSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGameInfoSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGameInfoSubsystem::SetCropMap(const TMap<FGrid, FCropData>& SavedMap)
{
	CropMap = SavedMap;
}

TMap<FGrid, FCropData>& UGameInfoSubsystem::GetCropMap()
{
	return CropMap;
}

void UGameInfoSubsystem::UpdateCropInfo(AFarmlandTile* TargetFarmlandTile)
{
	if (!IsValid(TargetFarmlandTile))
	{
		FMyDebug::Print(DEBUG_TEXT("FarmlandTile is Invalid."));
		return;
	}

	UGridSubsystem* gridSubsystem = GEngine->GetEngineSubsystem<UGridSubsystem>();

	FGrid grid = gridSubsystem->WorldToGrid(TargetFarmlandTile->GetActorLocation());

	FCropData cropData = TargetFarmlandTile->GetCropData();

	if (CropMap.Contains(grid))
	{
		FMyDebug::Print(DEBUG_TEXT("정보 변경"));
		CropMap[grid] = cropData;
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("새로 생성"));
		CropMap.Add(grid, cropData);
	}
}

void UGameInfoSubsystem::RemoveCropInfo(AFarmlandTile* TargetFarmlandTile)
{
	if (!IsValid(TargetFarmlandTile))
	{
		FMyDebug::Print(DEBUG_TEXT("FarmlandTile is Invalid."));
		return;
	}

	UGridSubsystem* gridSubsystem = GEngine->GetEngineSubsystem<UGridSubsystem>();

	FGrid grid = gridSubsystem->WorldToGrid(TargetFarmlandTile->GetActorLocation());
	FCropData cropData = TargetFarmlandTile->GetCropData();

	if (CropMap.Contains(grid))
	{
		FMyDebug::Print(DEBUG_TEXT("정보 삭제"));
		CropMap.Remove(grid);
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("없는 것을 삭제하려 함."));
	}
}

ELanguage UGameInfoSubsystem::GetGameLanguage() const
{
	return GameLanguage;
}
