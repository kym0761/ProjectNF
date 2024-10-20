// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Defines/Data.h"
#include "Defines/Enums.h"
#include "GameInfoSubsystem.generated.h"

class AFarmlandTile;

/**
 * 게임 플레이에 관한 정보를 저장하고 사용하기 위해 필요한 서브시스템
 * 플레이어가 게임을 하는 동안 정보가 계속 유지되어야 하므로 GameInstanceSubsystem을 사용함
 */
UCLASS()
class GAMECONTENTS_API UGameInfoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UGameInfoSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:

	/*게임 관련 재화 정보를 적어둘 위치*/
	UPROPERTY()
	int32 Money;

	//게임 내 농작물 키울때마다 업데이트가 될 farmlandtile의 정보를 보관하는 TMap
	UPROPERTY()
	TMap<FGrid, FCropData> CropMap;

	//인게임 현재 시간
	UPROPERTY()
	FGameDateTime CurrentGameTime;

public:

	void SetCropMap(const TMap<FGrid, FCropData>& SavedMap);
	TMap<FGrid, FCropData>& GetCropMap();

	UFUNCTION()
	void UpdateCropInfo(AFarmlandTile* TargetFarmlandTile);
	UFUNCTION()
	void RemoveCropInfo(AFarmlandTile* TargetFarmlandTile);


	void SetCurrentGameTime(FGameDateTime DateTimeVal);
	
	//일단 UI에서 접근하기 위해
	UFUNCTION(BlueprintCallable)
	FGameDateTime GetCurrentGameTime() const;
	
	void SetMoney(int32 MoneyVal);
	UFUNCTION(BlueprintCallable)
	int32 GetMoney() const;
};
