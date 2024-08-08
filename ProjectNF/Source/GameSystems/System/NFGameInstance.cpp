// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameInstance.h"
#include "NFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelper.h"

#include "Managers/GridManager.h"
#include "Managers/ElectricLinkManager.h"
#include "Managers/ObjectPoolManager.h"
#include "Managers/InventoryManager.h"
#include "Managers/DataManager.h"
#include "Managers/GameManager.h"
#include "Managers/ObjectManager.h"

//private manager
TObjectPtr<UGridManager> UNFGameInstance::GGridManager = nullptr;
TObjectPtr<UElectricLinkManager> UNFGameInstance::GElectricLinkManager = nullptr;
TObjectPtr<UObjectPoolManager> UNFGameInstance::GObjectPoolManager = nullptr;
TObjectPtr<UInventoryManager> UNFGameInstance::GInventoryManager = nullptr;
TObjectPtr<UDataManager> UNFGameInstance::GDataManager = nullptr;
TObjectPtr<UGameManager> UNFGameInstance::GGameManager = nullptr;
TObjectPtr<UObjectManager> UNFGameInstance::GObjectManager = nullptr;


UNFGameInstance::UNFGameInstance()
{
	PlayerName = TEXT("TempName");
	SaveSlotNumber = 123;
}

UNFGameInstance* UNFGameInstance::GetNFGameInstance()
{
	if (!GEngine)
	{
		return nullptr;
	}
	auto gameinst= Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GEngine->GetCurrentPlayWorld()));
	
	return gameinst;
}

void UNFGameInstance::Save()
{

	UNFSaveGame* saveGame = 
		Cast<UNFSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UNFSaveGame::StaticClass()));

	if (!IsValid(saveGame))
	{
		//saveGame 만들기 실패
		FMyDebug::Print(DEBUG_TEXT("세이브 실패"));
		return;
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("세이브 성공"));
	}

	//세이브에 플레이어 이름을 넣는다.
	saveGame->PlayerName = PlayerName;

	//인벤토리 데이터 세이브
	SaveInventory(saveGame);

	SaveFarmlandTile(saveGame);

	FString slotName = TEXT("Save") + FString::FromInt(SaveSlotNumber);

	//GameInstance에 있는 SlotNumber를 사용한다.
	UGameplayStatics::SaveGameToSlot(saveGame, slotName, 0);

}

void UNFGameInstance::Load(int32 SlotNumber)
{
	FString slotName = TEXT("Save") + FString::FromInt(SlotNumber);

	UNFSaveGame* saveGame =
		Cast<UNFSaveGame>(
			UGameplayStatics::LoadGameFromSlot(slotName, 0));


	if (!IsValid(saveGame))
	{
		//load 실패
		FMyDebug::Print(DEBUG_TEXT("로딩 실패"));

		//로드를 실패했어도 GameInstance는 초기화가 되어야함.
		InitNFGameInstance();

		//로드를 실패했어도, 일단 GameInstance의 SlotNumber는 기억해야함.
		SaveSlotNumber = SlotNumber;

		return;
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("Load 성공"));
	}

	//처음 로드할 때, 플레이어 이름과 Save의 SlotNumber를 먼저 넣음
	PlayerName = saveGame->PlayerName;
	SaveSlotNumber = SlotNumber;

	//GameInstance를 init한 후 Loading.
	InitNFGameInstance();

	//인벤토리 Load
	LoadInventory(saveGame);

	LoadFarmlandTile(saveGame);
}

void UNFGameInstance::SaveInventory(UNFSaveGame* SaveGame)
{
	//Inventory의 데이터를 전부 읽고 savegame에 인벤토리 정보를 저장함.

	auto& inventories = InventoryManager->GetAllInventories();

	SaveGame->InventorySave.Empty();

	for (auto& inventory : inventories)
	{
		FInventorySaveData inventorySave;
		inventorySave.InventoryID = inventory.Key;
		inventorySave.Items = inventory.Value->GetAllItems();

		SaveGame->InventorySave.Add(inventorySave);
	}

}

void UNFGameInstance::LoadInventory(UNFSaveGame* SaveGame)
{
	//savegame의 인벤토리 정보를 얻어 inventory manager를 세팅함.

	auto& inventorySave = SaveGame->InventorySave;

	InventoryManager->LoadInventories(inventorySave);


}

void UNFGameInstance::SaveFarmlandTile(UNFSaveGame* SaveGame)
{
	//GridManager에 저장된 FarmlandTile의 데이터를 SaveGame에 저장함

	auto& farmlandTileMap = GridManager->GetCropMap();

	TArray<FCropSaveData> saveArray;

	for (auto& i : farmlandTileMap)
	{
		FGrid& grid = i.Key;
		FCropData& cropData = i.Value;

		FCropSaveData cropSaveData;

		cropSaveData.CropData = cropData;
		cropSaveData.GridPosition = grid;

		saveArray.Add(cropSaveData);
	}

	SaveGame->CropSave = saveArray;
}

void UNFGameInstance::LoadFarmlandTile(UNFSaveGame* SaveGame)
{
	//SaveGame에 저장된 데이터를 GridManager로 옮김.

	auto& farmlandTiles = SaveGame->CropSave;

	TMap<FGrid, FCropData> farmlandTileMap;

	for (auto& i : farmlandTiles)
	{
		farmlandTileMap.Add(i.GridPosition, i.CropData);
	}

	GridManager->SetCropMap(farmlandTileMap);
}

void UNFGameInstance::InitManagers()
{
	FMyDebug::Print(DEBUG_TEXT("InitManagers Called."));

	// Manager를 추가할 때마다 이 부분을 추가해야함


	if (!IsValid(GridManager_BP) ||
		!IsValid(ElectricLinkManager_BP) ||
		!IsValid(ObjectPoolManager_BP) ||
		!IsValid(InventoryManager_BP) ||
		!IsValid(DataManager_BP) ||
		!IsValid(GameManager_BP) ||
		!IsValid(ObjectManager_BP)
		)
	{
		FMyDebug::Print(DEBUG_TEXT("Manager 블루프린트 중에 Set되지 않은 것이 존재함. BP_GameInstance를 확인할 것."));
		return;
	}


	//매니저 최초 생성 및 초기화
	{
		if (!IsValid(GridManager))
		{
			NewObject<UGridManager>(this, GridManager_BP);
			GridManager = NewObject<UGridManager>(this, GridManager_BP);
			GGridManager = GridManager;
		}

		if (!IsValid(ElectricLinkManager))
		{
			ElectricLinkManager = NewObject<UElectricLinkManager>(this, ElectricLinkManager_BP);
			GElectricLinkManager = ElectricLinkManager;
		}

		if (!IsValid(ObjectPoolManager))
		{
			ObjectPoolManager = NewObject<UObjectPoolManager>(this, ObjectPoolManager_BP);
			GObjectPoolManager = ObjectPoolManager;
		}

		if (!IsValid(InventoryManager))
		{
			InventoryManager = NewObject<UInventoryManager>(this, InventoryManager_BP);
			GInventoryManager = InventoryManager;
		}

		if (!IsValid(DataManager))
		{
			DataManager = NewObject<UDataManager>(this, DataManager_BP);
			GDataManager = DataManager;
		}

		if (!IsValid(GameManager))
		{
			GameManager = NewObject<UGameManager>(this, GameManager_BP);
			GGameManager = GameManager;
		}

		if (!IsValid(ObjectManager))
		{
			ObjectManager = NewObject<UObjectManager>(this, ObjectManager_BP);
			GObjectManager = ObjectManager;
		}

	}
	

	GridManager->InitManager();
	ElectricLinkManager->InitManager();
	ObjectPoolManager->InitManager();
	InventoryManager->InitManager();
	DataManager->InitManager();
	GameManager->InitManager();
	ObjectManager->InitManager();

	FMyDebug::Print(DEBUG_TEXT("인스턴스의 InitManagers()이 완료됨."));

	//ObjManager에 ObjPoolManager의 Spawn & Despawn을 연동함.
	ObjectManager->RequestObjectPoolSpawn.Clear();
	ObjectManager->RequestObjectPoolSpawn.BindDynamic(ObjectPoolManager, &UObjectPoolManager::SpawnInPool);
	ObjectManager->RequestObjectPoolDespawn.Clear();
	ObjectManager->RequestObjectPoolDespawn.BindDynamic(ObjectPoolManager, &UObjectPoolManager::DespawnToPool);
}

void UNFGameInstance::InitNFGameInstance()
{
	InitManagers();

}

TObjectPtr<UGridManager> UNFGameInstance::GetGridManager()
{
	return GGridManager;
}

TObjectPtr<UElectricLinkManager> UNFGameInstance::GetElectricLinkManager()
{
	return GElectricLinkManager;
}

TObjectPtr<UObjectPoolManager> UNFGameInstance::GetObjectPoolManager()
{
	return GObjectPoolManager;
}

TObjectPtr<UInventoryManager> UNFGameInstance::GetInventoryManager()
{
	return GInventoryManager;
}

TObjectPtr<UDataManager> UNFGameInstance::GetDataManager()
{
	return GDataManager;
}

TObjectPtr<UGameManager> UNFGameInstance::GetGameManager()
{
	return GGameManager;
}

TObjectPtr<UObjectManager> UNFGameInstance::GetObjectManager()
{
	return GObjectManager;
}
