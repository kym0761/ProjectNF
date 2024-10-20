// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Defines/Data.h"
#include "GridSubsystem.generated.h"

class AGridSetup;

/**
 * Grid는 GameInstance와 별개로 동작해도 될 것 같기에 UWorldSubsystem
 * 왜 별개냐면, Grid시스템은 World가 존재해야 의미가 있음.
 * GameInstance는 기본적으로 월드가 transient이므로 실제 월드의 오브젝트가 아님
 */

//WorldSubsystem으로 변경?
//Grid는 월드가 바뀔때마다 Setting이 필요할 수 있음
//예시) GridSetup을 Spawn한다라던지

UCLASS()
class GAMECONTENTS_API UGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	UGridSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	float CellSize = 200.0f;

	//게임 내 농작물 키울때마다 업데이트가 될 farmlandtile의 정보를 보관하는 TMap
	//TODO : 이 정보는 게임 플레이 정보기 때문에 다른 곳에서 저장해야할 필요가 있음.
	UPROPERTY()
	TMap<FGrid, FCropData> CropMap;

	UPROPERTY()
	TObjectPtr<AGridSetup> GridSetupRef;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;

};
