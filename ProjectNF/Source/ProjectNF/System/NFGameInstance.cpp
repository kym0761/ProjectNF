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

//private manager
TObjectPtr<UGridManager> UNFGameInstance::GGridManager = nullptr;
TObjectPtr<UElectricLinkManager> UNFGameInstance::GElectricLinkManager = nullptr;
TObjectPtr<UObjectPoolManager> UNFGameInstance::GObjectPoolManager = nullptr;
TObjectPtr<UInventoryManager> UNFGameInstance::GInventoryManager = nullptr;
TObjectPtr<UDataManager> UNFGameInstance::GDataManager = nullptr;

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
		return;
	}

	saveGame->PlayerName = PlayerName;
	saveGame->SaveSlotUserIndex = PlayerNumber;

	UGameplayStatics::SaveGameToSlot(saveGame, saveGame->SaveSlotName, saveGame->SaveSlotUserIndex);

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
		return;
	}

	PlayerName = saveGame->PlayerName;
	PlayerNumber = saveGame->SaveSlotUserIndex;

}

int32 UNFGameInstance::GetMoney() const
{
	return Money;
}

void UNFGameInstance::AddMoney(int32 InMoney)
{
	Money += InMoney;
}

bool UNFGameInstance::SpendMoney(int32 Pay)
{
	if (Pay > Money)
	{
		return false;
	}

	Money -= Pay;
	return true;
}


void UNFGameInstance::InitManagers()
{
	Debug::Print(DEBUG_TEXT("InitManagers Called."));

	if (!IsValid(GridManager_BP) ||
		!IsValid(ElectricLinkManager_BP) ||
		!IsValid(ObjectPoolManager_BP) ||
		!IsValid(InventoryManager_BP) ||
		!IsValid(DataManager_BP))
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

	}
	

	GridManager->InitManager();
	ElectricLinkManager->InitManager();
	ObjectPoolManager->InitManager();
	InventoryManager->InitManager();
	DataManager->InitManager();
}

void UNFGameInstance::Init()
{
	// ?

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
