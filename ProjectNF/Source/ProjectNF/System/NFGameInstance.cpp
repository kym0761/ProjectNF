// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameInstance.h"
#include "NFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelper.h"

#include "Managers/GridManager.h"
#include "Managers/ElectricLinkManager.h"
#include "Managers/ObjectPoolManager.h"
#include "Managers/InventoryManager.h"

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

bool UNFGameInstance::GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out)
{
	//빈 아이템 ID
	if (ItemID.IsNone())
	{
		Debug::Print(DEBUG_TEXT("Empty ItemID"));
		return false;
	}

	//존재하지 않는 아이템 데이터
	if (!ItemSheetDataMap.Contains(ItemID))
	{
		Debug::Print(DEBUG_TEXT("Invalid Item ID"));
		return false;
	}

	Out = ItemSheetDataMap[ItemID];
	return true;
}

bool UNFGameInstance::IsValidItem(const FName& ItemID) const
{
	//Map에 존재하면 아이템 존재함
	if (ItemSheetDataMap.Contains(ItemID))
	{
		return true;
	}

	//존재하지 않음
	return false;
}

FCropSheetData UNFGameInstance::GetCropDataFromSheet(const FName& CropID)
{
	//빈 Crop ID
	if (CropID.IsNone())
	{
		Debug::Print(DEBUG_TEXT("Empty CropID"));
		return FCropSheetData();
	}

	//Data Table이 아직 없음
	if (!IsValid(CropSheetTable))
	{
		Debug::Print(DEBUG_TEXT("Crop Sheet Table Not Set"));
		return FCropSheetData();
	}


	//존재하는 아이템이면 결과 도출 및 true
	FCropSheetData* cropSheetData = CropSheetTable->FindRow<FCropSheetData>(CropID, "");
	if (cropSheetData != nullptr)
	{

		return *cropSheetData;
	}

	//존재하지 않는 아이템 정보
	return FCropSheetData();
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

void UNFGameInstance::Init()
{
	//if (!IsValid(ItemDataTable))
	//{
	//	Debug::Print(DEBUG_TEXT("Item Data Table Not set"));
	//	return;
	//}

	//if (!IsValid(CropSheetTable))
	//{
	//	Debug::Print(DEBUG_TEXT("Crop Sheet Table Not set"));
	//	return;
	//}

	IncludeSheetDataToMap<FItemSheetData>(ItemSheetDataMap, ItemDataTable);

	IncludeSheetDataToMap<FCropSheetData>(CropSheetDataMap, CropSheetTable);

	//{
	//	auto rowNames = ItemDataTable->GetRowNames();
	//	for (auto rowName : rowNames)
	//	{
	//		FItemSheetData* sheetData = ItemDataTable->FindRow<FItemSheetData>(rowName, "");
	//		if (!sheetData)
	//		{
	//			Debug::Print(DEBUG_TEXT("Warning! : Item sheetData nullptr"));
	//			continue;
	//		}

	//		ItemSheetDataMap.Add(rowName, *sheetData);
	//	}

	//	//for (auto i : ItemSheetDataMap)
	//	//{
	//	//	FString str = FString::Printf(TEXT("key : %s, Value : %s"), *i.Key.ToString(), *i.Value.ItemNameID.ToString());

	//	//	Debug::Print(DEBUG_STRING(str));
	//	//}
	//}

	//{
	//	auto rowNames = CropSheetTable->GetRowNames();
	//	for (auto rowName : rowNames)
	//	{
	//		FCropSheetData* sheetData = CropSheetTable->FindRow<FCropSheetData>(rowName, "");
	//		if (!sheetData)
	//		{
	//			Debug::Print(DEBUG_TEXT("Warning! : Crop sheetData nullptr"));
	//			continue;
	//		}
	//		CropSheetDataMap.Add(rowName, *sheetData);
	//	}

	//}

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
