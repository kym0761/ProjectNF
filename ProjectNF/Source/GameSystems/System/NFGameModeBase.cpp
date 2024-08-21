// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Kismet/GameplayStatics.h"

//#include "NFGameInstance.h"
//#include "Engine/GameInstance.h"
#include "Subsystems/GameInfoSubsystem.h"
#include "Subsystems/GridSubsystem.h"
#include "Subsystems/ObjectSubsystem.h"
#include "Subsystems/SheetDataSubsystem.h"
#include "Subsystems/InventorySubsystem.h"

#include "GameFarm/FarmlandTile.h"
#include "DebugHelper.h"

#include "GameItem/Item/ItemPickup.h"


ANFGameModeBase::ANFGameModeBase()
{

}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	CreateAllSavedCrop();
	SetExistItemsInMap();
	//level 시작시 electric manager 다시 시동
	//TODO : subsystem 생성 및 가동

	//GEngine->GetEngineSubsystem<U>
	//UNFGameInstance::RestartLinkManager();

}

void ANFGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void ANFGameModeBase::CreateAllSavedCrop()
{
	//이 게임 모드가 활성화된다면, 기존에 저장된 Crop데이터를 읽어 맵에 Spawn한다.

	//FMyDebug::Print(DEBUG_TEXT("Crop Load to Unreal Map"));

	auto gameinfoSubsystem = GetGameInstance()->GetSubsystem<UGameInfoSubsystem>();
	auto gridSubsystem = GEngine->GetEngineSubsystem<UGridSubsystem>();
	auto objectSubsystem = GetGameInstance()->GetSubsystem<UObjectSubsystem>();
	auto sheetDataSubsystem = GetGameInstance()->GetSubsystem<USheetDataSubsystem>();
	auto& cropMap = gameinfoSubsystem->GetCropMap();

	for (auto& i : cropMap)
	{
		FGrid grid = i.Key;
		FCropData cropData = i.Value;

		AFarmlandTile* farmtile =
			Cast<AFarmlandTile>(objectSubsystem->Spawn(TEXT("FarmlandTile"), gridSubsystem->GridToWorld(grid)));

		//farmtile에 CropData와 Spawn을 요청하는 기능을 bind해야한다.
		farmtile->RequestCropSheetData.BindUObject(sheetDataSubsystem, &USheetDataSubsystem::GetCropData);
		//작물 아이템을 Spawn 요청하는 기능 Bind
		farmtile->RequestSpawnItemPickup.BindUObject(objectSubsystem,&UObjectSubsystem::Spawn);

		farmtile->RequestUpdateCropData.BindUObject(gameinfoSubsystem,&UGameInfoSubsystem::UpdateCropInfo);
		farmtile->RequestRemoveCropData.BindUObject(gameinfoSubsystem, &UGameInfoSubsystem::RemoveCropInfo);

		//! GridManager의 정보가 우선이므로, 
		//! Farmtile을 생성했을 때 이 farmtile의 정보로 gridManager를 세팅하려는 시도를 하면 안됨.

		farmtile->SetInfo(cropData);
	}

}

void ANFGameModeBase::SetExistItemsInMap()
{
	//맵에 미리 존재하는 액터들은 ObjectManager로 생성된 것이 아니기 때문에 GameMode에서 처리해준다.

	auto sheetDataSubsystem = GetGameInstance()->GetSubsystem<USheetDataSubsystem>();
	auto objectSubsystem = GetGameInstance()->GetSubsystem<UObjectSubsystem>();
	auto inventorySubsystem = GetGameInstance()->GetSubsystem<UInventorySubsystem>();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemPickup::StaticClass(), actors);

	for (auto i : actors)
	{
		AItemPickup* itemPickup = Cast<AItemPickup>(i);
		if (!IsValid(itemPickup))
		{
			continue;
		}

		itemPickup->RequestItemData.BindUObject(sheetDataSubsystem , &USheetDataSubsystem::GetItemData);
		itemPickup->RequestDespawn.BindUObject(objectSubsystem , &UObjectSubsystem::Despawn);
		itemPickup->RequestAddItem.BindUObject(inventorySubsystem ,&UInventorySubsystem::AddItemToTargetInventory);

		itemPickup->SetItemPickupData(itemPickup->GetPickupItemData());
	}

}
