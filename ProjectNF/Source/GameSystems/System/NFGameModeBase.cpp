// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "NFGameInstance.h"
#include "Managers/GridManager.h"
#include "Managers/ObjectManager.h"
#include "Managers/DataManager.h"
#include "Managers/ElectricLinkManager.h"
#include "GameFarm/FarmlandTile.h"
#include "DebugHelper.h"


ANFGameModeBase::ANFGameModeBase()
{

}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	CreateAllSavedCrop();

	//level 시작시 electric manager 다시 시동
	UNFGameInstance::GetElectricLinkManager()->InitManager();
}

void ANFGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void ANFGameModeBase::CreateAllSavedCrop()
{
	FMyDebug::Print(DEBUG_TEXT("Crop Load to Unreal Map"));

	auto objManager = UNFGameInstance::GetObjectManager();
	auto gridManager = UNFGameInstance::GetGridManager();
	auto dataManager = UNFGameInstance::GetDataManager();

	auto& cropMap = gridManager->GetCropMap();

	for (auto& i : cropMap)
	{
		FGrid grid = i.Key;
		FCropData cropData = i.Value;

		auto farmtile = Cast<AFarmlandTile>(objManager->Spawn(TEXT("FarmlandTile"), gridManager->GridToWorld(grid)));
		
		//farmtile에 CropData와 Spawn을 요청하는 기능을 bind해야한다.
		farmtile->RequestCropSheetData.BindDynamic(dataManager, &UDataManager::GetCropData);
		//작물 아이템을 Spawn 요청하는 기능 Bind
		farmtile->RequestSpawnItemPickup.BindDynamic(objManager, &UObjectManager::Spawn);

		farmtile->RequestUpdateCropData.BindDynamic(gridManager, &UGridManager::UpdateCropInfo);
		farmtile->RequestRemoveCropData.BindDynamic(gridManager, &UGridManager::RemoveCropInfo);

		//! GridManager의 정보가 우선이므로, 
		//! Farmtile을 생성했을 때 이 farmtile의 정보로 gridManager를 세팅하려는 시도를 하면 안됨.

		farmtile->SetInfo(cropData);
	}

}
