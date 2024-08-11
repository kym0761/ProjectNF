// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Data.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "GridManager.generated.h"


class AFarmlandTile;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMESYSTEMS_API UGridManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UGridManager();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
		float CellSize = 200.0f;

	//게임 내 농작물 키울때마다 업데이트가 될 farmlandtile의 정보를 보관하는 TMap
	UPROPERTY()
	TMap<FGrid, FCropData> CropMap;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;

	void SetCropMap(const TMap<FGrid, FCropData>& SavedMap);
	TMap<FGrid, FCropData>& GetCropMap();

	UFUNCTION()
	void UpdateCropInfo(AFarmlandTile* TargetFarmlandTile);
	UFUNCTION()
	void RemoveCropInfo(AFarmlandTile* TargetFarmlandTile);

public:

	virtual void InitManager() override;
};
