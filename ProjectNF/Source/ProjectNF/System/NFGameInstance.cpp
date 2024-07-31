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
	PlayerNumber = 1;

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
	TObjectPtr<UNFSaveGame> saveGame = 
		Cast<UNFSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UNFSaveGame::StaticClass()));

	if (!IsValid(saveGame))
	{
		//saveGame 만들기 실패
		Debug::Print(DEBUG_TEXT("SaveGame Making Failed.."));
		return;
	}

	saveGame->PlayerName = PlayerName;
	saveGame->SaveSlotUserIndex = PlayerNumber;

	//인벤토리 데이터 세이브
	SaveInventory(saveGame);


	UGameplayStatics::SaveGameToSlot(saveGame, PlayerName, PlayerNumber);

}

void UNFGameInstance::Load()
{
	FString saveSlotName = TEXT("TempName");
	int32 userIndex = 1;

	TObjectPtr<UNFSaveGame> saveGame =
		Cast<UNFSaveGame>(
			UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex));

	if (!IsValid(saveGame))
	{
		//load 실패
		Debug::Print(DEBUG_TEXT("SaveGame Loading Failed.."));

		//Load를 실패했어도 GameInstance는 초기화가 되어야함.
		InitNFGameInstance();

		return;
	}

	PlayerName = saveGame->PlayerName;
	PlayerNumber = saveGame->SaveSlotUserIndex;

	//GameInstance를 init한 후 Loading.
	InitNFGameInstance();

	//인벤토리 Load
	LoadInventory(saveGame);
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

void UNFGameInstance::InitManagers()
{
	Debug::Print(DEBUG_TEXT("InitManagers Called."));

	if (!IsValid(GridManager_BP) ||
		!IsValid(ElectricLinkManager_BP) ||
		!IsValid(ObjectPoolManager_BP) ||
		!IsValid(InventoryManager_BP) ||
		!IsValid(DataManager_BP) ||
		!IsValid(GameManager_BP) ||
		!IsValid(ObjectManager_BP)
		)
	{
		Debug::Print(DEBUG_TEXT("Manager blueprint Are Not Set."));
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

	Debug::Print(DEBUG_TEXT("Instance's Managers Init Completed."));

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
