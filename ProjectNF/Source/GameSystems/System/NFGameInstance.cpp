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

#include "GameItem/Inventory/InventoryComponent.h"

#include "Subsystems/GridSubsystem.h"
#include "Subsystems/GameInfoSubsystem.h"
#include "Subsystems/InventorySubsystem.h"
#include "Subsystems/ObjectPoolSubsystem.h"
#include "Subsystems/ObjectSubsystem.h"
#include "Subsystems/SheetDataSubsystem.h"

////private manager
//TObjectPtr<UGridManager> UNFGameInstance::GGridManager = nullptr;
//TObjectPtr<UElectricLinkManager> UNFGameInstance::GElectricLinkManager = nullptr;
//TObjectPtr<UObjectPoolManager> UNFGameInstance::GObjectPoolManager = nullptr;
//TObjectPtr<UInventoryManager> UNFGameInstance::GInventoryManager = nullptr;
//TObjectPtr<UDataManager> UNFGameInstance::GDataManager = nullptr;
//TObjectPtr<UGameManager> UNFGameInstance::GGameManager = nullptr;
//TObjectPtr<UObjectManager> UNFGameInstance::GObjectManager = nullptr;


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

void UNFGameInstance::Init()
{
	Super::Init();


	//엔진 서브시스템이 initialize되는 동안은 content 폴더에 접근이 불가능함.
	//게임 인스턴스 시작시 시도하면 정상적으로 동작함. 
	auto objectSubsystem = GEngine->GetEngineSubsystem<UObjectSubsystem>();
	if (IsValid(objectSubsystem))
	{
		objectSubsystem->LoadAllBlueprints();
	}
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

	/*
	//인벤토리 데이터 세이브
	SaveInventory(saveGame);

	//작물 정보 세이브
	SaveFarmlandTile(saveGame);
	*/

	SaveGameInfo(saveGame);

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

	LoadGameInfo(saveGame);
}



void UNFGameInstance::SaveGameInfo(UNFSaveGame* SaveGame)
{
	auto gameInfoSubsystem = GetSubsystem<UGameInfoSubsystem>();

	//게임 시간
	{
		auto currentGameTime = gameInfoSubsystem->GetCurrentGameTime();
		SaveGame->CurrentGameTime = currentGameTime;
	}
	
	//farm 작물 정보
	{
		//보관된 FarmlandTile의 데이터를 SaveGame에 저장함

		auto& farmlandTileMap = gameInfoSubsystem->GetCropMap();

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

	//인벤토리
	{
		//Inventory의 데이터를 전부 읽고 savegame에 인벤토리 정보를 저장함.

		auto& inventories = GetSubsystem<UInventorySubsystem>()->GetAllInventories();

		SaveGame->InventorySave.Empty();

		for (auto& inventory : inventories)
		{
			FInventorySaveData inventorySave;
			inventorySave.InventoryID = inventory.Key;
			inventorySave.Items = inventory.Value->GetAllItems();

			SaveGame->InventorySave.Add(inventorySave);
		}
	}

	//Money
	{
		int money = gameInfoSubsystem->GetMoney();
		SaveGame->Money = money;
	}
}

void UNFGameInstance::LoadGameInfo(UNFSaveGame* SaveGame)
{

	auto gameInfoSubsystem = GetSubsystem<UGameInfoSubsystem>();

	//게임 시간
	{
		gameInfoSubsystem->SetCurrentGameTime(SaveGame->CurrentGameTime);
	}

	//Farm 작물 정보
	{
		//SaveGame에 저장된 데이터를 실제 게임에 옮김.
		auto& farmlandTiles = SaveGame->CropSave;

		TMap<FGrid, FCropData> farmlandTileMap;

		for (auto& i : farmlandTiles)
		{
			farmlandTileMap.Add(i.GridPosition, i.CropData);
		}

		gameInfoSubsystem->SetCropMap(farmlandTileMap);
	}

	//인벤토리
	{
		//세이브의 인벤토리 데이터를 실제 게임으로 옮김.

		auto& inventorySave = SaveGame->InventorySave;
		GetSubsystem<UInventorySubsystem>()->LoadInventories(inventorySave);
	}

	//Money
	{
		gameInfoSubsystem->SetMoney(SaveGame->Money);
	}

}

void UNFGameInstance::InitManagers()
{
	//FMyDebug::Print(DEBUG_TEXT("InitManagers Called."));

	//// Manager를 추가할 때마다 이 부분을 추가해야함


	//if (!IsValid(GridManager_BP) ||
	//	!IsValid(ElectricLinkManager_BP) ||
	//	!IsValid(ObjectPoolManager_BP) ||
	//	!IsValid(InventoryManager_BP) ||
	//	!IsValid(DataManager_BP) ||
	//	!IsValid(GameManager_BP) ||
	//	!IsValid(ObjectManager_BP)
	//	)
	//{
	//	FMyDebug::Print(DEBUG_TEXT("Manager 블루프린트 중에 Set되지 않은 것이 존재함. BP_GameInstance를 확인할 것."));
	//	return;
	//}


	////매니저 최초 생성 및 초기화
	//{
	//	if (!IsValid(GridManager))
	//	{
	//		NewObject<UGridManager>(this, GridManager_BP);
	//		GridManager = NewObject<UGridManager>(this, GridManager_BP);
	//		GGridManager = GridManager;
	//	}

	//	if (!IsValid(ElectricLinkManager))
	//	{
	//		ElectricLinkManager = NewObject<UElectricLinkManager>(this, ElectricLinkManager_BP);
	//		GElectricLinkManager = ElectricLinkManager;
	//	}

	//	if (!IsValid(ObjectPoolManager))
	//	{
	//		ObjectPoolManager = NewObject<UObjectPoolManager>(this, ObjectPoolManager_BP);
	//		GObjectPoolManager = ObjectPoolManager;
	//	}

	//	if (!IsValid(InventoryManager))
	//	{
	//		InventoryManager = NewObject<UInventoryManager>(this, InventoryManager_BP);
	//		GInventoryManager = InventoryManager;
	//	}

	//	if (!IsValid(DataManager))
	//	{
	//		DataManager = NewObject<UDataManager>(this, DataManager_BP);
	//		GDataManager = DataManager;
	//	}

	//	if (!IsValid(GameManager))
	//	{
	//		GameManager = NewObject<UGameManager>(this, GameManager_BP);
	//		GGameManager = GameManager;
	//	}

	//	if (!IsValid(ObjectManager))
	//	{
	//		ObjectManager = NewObject<UObjectManager>(this, ObjectManager_BP);
	//		GObjectManager = ObjectManager;
	//	}

	//}
	//

	//GridManager->InitManager();
	//ElectricLinkManager->InitManager();
	//ObjectPoolManager->InitManager();
	//InventoryManager->InitManager();
	//DataManager->InitManager();
	//GameManager->InitManager();
	//ObjectManager->InitManager();

	//FMyDebug::Print(DEBUG_TEXT("인스턴스의 InitManagers()이 완료됨."));

	////ObjManager에 ObjPoolManager의 Spawn & Despawn을 연동함.
	//ObjectManager->RequestObjectPoolSpawn.Unbind();
	//ObjectManager->RequestObjectPoolSpawn.BindUObject(ObjectPoolManager, &UObjectPoolManager::SpawnInPool);
	//ObjectManager->RequestObjectPoolDespawn.Unbind();
	//ObjectManager->RequestObjectPoolDespawn.BindUObject(ObjectPoolManager, &UObjectPoolManager::DespawnToPool);

}

void UNFGameInstance::InitNFGameInstance()
{
	InitManagers();

}

//TObjectPtr<UGridManager> UNFGameInstance::GetGridManager()
//{
//	return GGridManager;
//}
//
//TObjectPtr<UElectricLinkManager> UNFGameInstance::GetElectricLinkManager()
//{
//	return GElectricLinkManager;
//}
//
//TObjectPtr<UObjectPoolManager> UNFGameInstance::GetObjectPoolManager()
//{
//	return GObjectPoolManager;
//}
//
//TObjectPtr<UInventoryManager> UNFGameInstance::GetInventoryManager()
//{
//	return GInventoryManager;
//}
//
//TObjectPtr<UDataManager> UNFGameInstance::GetDataManager()
//{
//	return GDataManager;
//}
//
//TObjectPtr<UGameManager> UNFGameInstance::GetGameManager()
//{
//	return GGameManager;
//}
//
//TObjectPtr<UObjectManager> UNFGameInstance::GetObjectManager()
//{
//	return GObjectManager;
//}

//Static Functions of Managers

//FItemSheetData UNFGameInstance::GetItemData(const FName& ItemID)
//{
//	USheetDataSubsystem* subsystem = UGameplayStatics::GetGameInstance(
//		GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World())->GetSubsystem<USheetDataSubsystem>();
//
//	return subsystem->GetItemData(ItemID);
//}
//
//bool UNFGameInstance::IsValidItem(const FName& ItemID)
//{
//	return GDataManager->IsValidItem(ItemID);
//}
//
//FCropSheetData UNFGameInstance::GetCropData(const FName& CropID)
//{
//	return GDataManager->GetCropData(CropID);
//}
//
//bool UNFGameInstance::IsValidCrop(const FName& CropID)
//{
//	return GDataManager->IsValidCrop(CropID);
//}
//
//FAbilitySheetData UNFGameInstance::GetAbilityData(const FName& AbilityID)
//{
//	return GDataManager->GetAbilityData(AbilityID);
//}
//
//bool UNFGameInstance::IsValidAbility(const FName& AbilityID)
//{
//	return GDataManager->IsValidAbility(AbilityID);
//}
//
//FLanguageSheetData UNFGameInstance::GetLanguageData(const FName& LanguageID)
//{
//	return GDataManager->GetLanguageData(LanguageID);
//}
//
//bool UNFGameInstance::IsValidLanguageData(const FName& LanguageID)
//{
//	return GDataManager->IsValidLanguageData(LanguageID);
//}
//
//void UNFGameInstance::RestartLinkManager()
//{
//	GElectricLinkManager->RestartLinkManager();
//}
//
//FGrid UNFGameInstance::WorldToGrid(const FVector& WorldLocation)
//{
//	return GGridManager->WorldToGrid(WorldLocation);
//}
//
//FVector UNFGameInstance::GridToWorld(const FGrid& Grid)
//{
//	return GGridManager->GridToWorld(Grid);
//}
//
//bool UNFGameInstance::IsSomethingExistOnGrid(const FGrid& Grid)
//{
//	return GGridManager->IsSomethingExistOnGrid(Grid);
//}
//
//void UNFGameInstance::SetCropMap(const TMap<FGrid, FCropData>& SavedMap)
//{
//	GGridManager->SetCropMap(SavedMap);
//}
//
//TMap<FGrid, FCropData>& UNFGameInstance::GetCropMap()
//{
//	return GGridManager->GetCropMap();
//}
//
//void UNFGameInstance::UpdateCropInfo(AFarmlandTile* TargetFarmlandTile)
//{
//	GGridManager->UpdateCropInfo(TargetFarmlandTile);
//}
//
//void UNFGameInstance::RemoveCropInfo(AFarmlandTile* TargetFarmlandTile)
//{
//	GGridManager->RemoveCropInfo(TargetFarmlandTile);
//}
//
//UInventoryObject* UNFGameInstance::TryGetInventory(FString InventoryOwner)
//{
//	return GInventoryManager->TryGetInventory(InventoryOwner);
//}
//
//void UNFGameInstance::LoadInventories(const TArray<FInventorySaveData>& InventorySaveData)
//{
//	GInventoryManager->LoadInventories(InventorySaveData);
//}
//
//TMap<FString, UInventoryObject*>& UNFGameInstance::GetAllInventories()
//{
//	return GInventoryManager->GetAllInventories();
//}
//
//bool UNFGameInstance::AddItemToTargetInventory(AActor* InventoryOwner, const FItemSlotData& SlotData)
//{
//	//인벤토리를 찾고, 인벤토리에 아이템을 넣는다.
//
//	auto inventoryComponent = InventoryOwner->FindComponentByClass<UInventoryComponent>();
//
//	if (!IsValid(inventoryComponent))
//	{
//		FMyDebug::Print(DEBUG_TEXT("No Inventory comp."));
//		return false;
//	}
//
//	bool bAdded = inventoryComponent->AddItemToInventory(SlotData);
//
//	return bAdded;
//}
//
//AActor* UNFGameInstance::Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation)
//{
//	return GObjectManager->Spawn(ToSpawnClassName, Location, Rotation);
//}
//
//UUserWidget* UNFGameInstance::CreateWidgetBlueprint(FString ToCreateWidgetName, APlayerController* WidgetOwner)
//{
//	return GObjectManager->CreateWidgetFromName(ToCreateWidgetName, WidgetOwner);
//}
//
//void UNFGameInstance::Despawn(AActor* DespawnTarget)
//{
//	GObjectManager->Despawn(DespawnTarget);
//}
//
//UNiagaraComponent* UNFGameInstance::SpawnNiagaraSystem(FString ToSpawnNiagaraName, const FVector& Location, const FRotator& Rotation)
//{
//	return GObjectManager->SpawnNiagaraSystem(ToSpawnNiagaraName, Location, Rotation);
//}
//
//AActor* UNFGameInstance::SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation)
//{
//	return GObjectPoolManager->SpawnInPool(WorldContext, PoolableBP, Location, Rotation);
//}
//
//void UNFGameInstance::DespawnToPool(AActor* PoolableActor)
//{
//	GObjectPoolManager->DespawnToPool(PoolableActor);
//}
//
//void UNFGameInstance::ClearObjectPooling()
//{
//	GObjectPoolManager->ClearObjectPooling();
//}
