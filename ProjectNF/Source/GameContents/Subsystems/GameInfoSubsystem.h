// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Defines/Data.h"
#include "Defines/Enums.h"
#include "GameInfoSubsystem.generated.h"

class AFarmlandTile;

/**
 * 
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

	/*게임 관련 재화 정보?*/
	UPROPERTY()
	int32 Money;

	//게임 내 농작물 키울때마다 업데이트가 될 farmlandtile의 정보를 보관하는 TMap
	UPROPERTY()
	TMap<FGrid, FCropData> CropMap;

	//게임 언어 정보?
	ELanguage GameLanguage;

public:

	void SetCropMap(const TMap<FGrid, FCropData>& SavedMap);
	TMap<FGrid, FCropData>& GetCropMap();

	UFUNCTION()
	void UpdateCropInfo(AFarmlandTile* TargetFarmlandTile);
	UFUNCTION()
	void RemoveCropInfo(AFarmlandTile* TargetFarmlandTile);

	ELanguage GetGameLanguage() const;

};
