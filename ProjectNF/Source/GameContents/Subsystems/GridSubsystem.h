// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Defines/Data.h"
#include "GridSubsystem.generated.h"

/**
 * Grid는 게임인스턴스와 별개로 동작해도 될 것 같기에 EngineSubsystem
 * 왜 별개냐면, Grid시스템은 World가 존재해야한다. 게임인스턴스는 기본적으로 월드가 transient이므로 실제 월드의 오브젝트가 아님
 * 엔진서브시스템으로 관리하면 world값이 그대로 존재함
 */
UCLASS()
class GAMECONTENTS_API UGridSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:

	UGridSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	float CellSize = 200.0f;

	//게임 내 농작물 키울때마다 업데이트가 될 farmlandtile의 정보를 보관하는 TMap
	//TODO : 이 정보는 게임 플레이 정보기 때문에 다른 곳에서 저장해야할 필요가 있음.
	UPROPERTY()
	TMap<FGrid, FCropData> CropMap;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;

	/*여기 부터는 게임 플레이 정보라 옮길 예정*/

	//void SetCropMap(const TMap<FGrid, FCropData>& SavedMap);
	//TMap<FGrid, FCropData>& GetCropMap();

	//UFUNCTION()
	//void UpdateCropInfo(AFarmlandTile* TargetFarmlandTile);
	//UFUNCTION()
	//void RemoveCropInfo(AFarmlandTile* TargetFarmlandTile);

};
