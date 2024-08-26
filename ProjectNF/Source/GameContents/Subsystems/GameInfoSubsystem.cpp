// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfoSubsystem.h"

#include "DebugHelper.h"
#include "GameFarm/FarmlandTile.h"
#include "Subsystems/GridSubsystem.h"

UGameInfoSubsystem::UGameInfoSubsystem()
{
}

void UGameInfoSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//시간 초기값 : 0년 3월 1일 6시 0분
	CurrentGameTime = FGameDateTime(0, 3, 1, 6, 0);
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

	UGridSubsystem* gridSubsystem = GEngine->GetCurrentPlayWorld()->GetSubsystem<UGridSubsystem>();

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

	UGridSubsystem* gridSubsystem = // GEngine->GetEngineSubsystem<UGridSubsystem>();
		GEngine->GetCurrentPlayWorld()->GetSubsystem<UGridSubsystem>();

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

void UGameInfoSubsystem::SetCurrentGameTime(FGameDateTime DateTimeVal)
{
	CurrentGameTime = DateTimeVal;
}

FGameDateTime UGameInfoSubsystem::GetCurrentGameTime() const
{
	return CurrentGameTime;
}

void UGameInfoSubsystem::SetMoney(int32 MoneyVal)
{
	Money = MoneyVal;
}

int32 UGameInfoSubsystem::GetMoney() const
{
	return Money;
}
