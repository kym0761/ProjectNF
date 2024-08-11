// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "NFGameInstance.h"
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
	UNFGameInstance::RestartLinkManager();

}

void ANFGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void ANFGameModeBase::CreateAllSavedCrop()
{
	//이 게임 모드가 활성화된다면, 기존에 저장된 Crop데이터를 읽어 맵에 Spawn한다.

	//FMyDebug::Print(DEBUG_TEXT("Crop Load to Unreal Map"));

	auto& cropMap = UNFGameInstance::GetCropMap();

	for (auto& i : cropMap)
	{
		FGrid grid = i.Key;
		FCropData cropData = i.Value;

		AFarmlandTile* farmtile = Cast<AFarmlandTile>(UNFGameInstance::Spawn(TEXT("FarmlandTile"), UNFGameInstance::GridToWorld(grid)));
		
		//farmtile에 CropData와 Spawn을 요청하는 기능을 bind해야한다.
		farmtile->RequestCropSheetData.BindStatic(&UNFGameInstance::GetCropData);
		//작물 아이템을 Spawn 요청하는 기능 Bind
		farmtile->RequestSpawnItemPickup.BindStatic(&UNFGameInstance::Spawn);

		farmtile->RequestUpdateCropData.BindStatic(&UNFGameInstance::UpdateCropInfo);
		farmtile->RequestRemoveCropData.BindStatic(&UNFGameInstance::RemoveCropInfo);

		//! GridManager의 정보가 우선이므로, 
		//! Farmtile을 생성했을 때 이 farmtile의 정보로 gridManager를 세팅하려는 시도를 하면 안됨.

		farmtile->SetInfo(cropData);
	}

}

void ANFGameModeBase::SetExistItemsInMap()
{
	//맵에 미리 존재하는 액터들은 ObjectManager로 생성된 것이 아니기 때문에 GameMode에서 처리해준다.

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemPickup::StaticClass(), actors);

	for (auto i : actors)
	{
		AItemPickup* itemPickup = Cast<AItemPickup>(i);
		if (!IsValid(itemPickup))
		{
			continue;
		}
		itemPickup->RequestItemData.BindStatic(&UNFGameInstance::GetItemData);
		itemPickup->RequestDespawn.BindStatic(&UNFGameInstance::DespawnToPool);
		itemPickup->RequestAddItem.BindStatic(&UNFGameInstance::AddItemToTargetInventory);

		itemPickup->SetItemPickupData(itemPickup->GetPickupItemData());
	}

}
