// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameInstance.h"
#include "NFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelper.h"

#include "Grid/GridManager.h"
#include "PuzzleActors/ElectricLink/ElectricLinkManager.h"
#include "ObjectPoolManager.h"
#include "Inventory/InventoryManager.h"

//private manager
TObjectPtr<UGridManager> UNFGameInstance::GGridManager = nullptr;
TObjectPtr<UElectricLinkManager> UNFGameInstance::GElectricLinkManager = nullptr;
TObjectPtr<UObjectPoolManager> UNFGameInstance::GObjectPoolManager = nullptr;
TObjectPtr<UInventoryManager> UNFGameInstance::GInventoryManager = nullptr;

UNFGameInstance::UNFGameInstance()
{
	PlayerName = TEXT("TempName");
	PlayerNumber = 1;

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

bool UNFGameInstance::GetItemDataFromDataTable(const FName& ItemID, FItemBaseData& Out)
{

	//빈 아이템 ID
	if (ItemID.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty ItemID"));
		return false;
	}

	//Data Table이 아직 없음
	if (!IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Data Table Not Set"));
		return false;
	}


	//존재하는 아이템이면 결과 도출 및 true
	FItemBaseData* itemBaseData = ItemDataTable->FindRow<FItemBaseData>(ItemID, "");
	if (itemBaseData != nullptr)
	{
		Out = *itemBaseData;
		return true;
	}

	//존재하지 않는 아이템 정보
	return false;
}

bool UNFGameInstance::IsValidItem(const FName& ItemID) const
{
	//Data Table이 아직 없음
	if (!IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Data Table Not Set"));
		return false;
	}


	//존재하는 아이템이면 true
	FItemBaseData* itemBaseData = ItemDataTable->FindRow<FItemBaseData>(ItemID, "");
	if (itemBaseData != nullptr)
	{
		return true;
	}

	//존재하지 않는 아이템
	return false;
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

	//매니저 최초 생성 및 초기화
	{
		if (!IsValid(GridManager))
		{
			GridManager = NewObject<UGridManager>(this);
			GGridManager = GridManager;
		}

		if (!IsValid(ElectricLinkManager))
		{
			ElectricLinkManager = NewObject<UElectricLinkManager>(this);
			GElectricLinkManager = ElectricLinkManager;
		}

		if (!IsValid(ObjectPoolManager))
		{
			ObjectPoolManager = NewObject<UObjectPoolManager>(this);
			GObjectPoolManager = ObjectPoolManager;
		}

		if (!IsValid(InventoryManager))
		{
			InventoryManager = NewObject<UInventoryManager>(this);
			GInventoryManager = InventoryManager;
		}
	}
	

	GridManager->ManagerInit();
	ElectricLinkManager->ManagerInit();
	ObjectPoolManager->ManagerInit();
	InventoryManager->ManagerInit();

}

TObjectPtr<UGridManager> UNFGameInstance::GetGridManager()
{
	return GGridManager;
}

TObjectPtr<UElectricLinkManager> UNFGameInstance::GetElectricLinkManager()
{
	return GElectricLinkManager;
}
