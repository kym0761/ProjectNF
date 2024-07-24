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
		//saveGame ����� ����
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
		//load ����
		return;
	}

	PlayerName = saveGame->PlayerName;
	PlayerNumber = saveGame->SaveSlotUserIndex;

}

bool UNFGameInstance::GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out)
{
	//�� ������ ID
	if (ItemID.IsNone())
	{
		Debug::Print(DEBUG_TEXT("Empty ItemID"));
		return false;
	}

	//�������� �ʴ� ������ ������
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
	//Map�� �����ϸ� ������ ������
	if (ItemSheetDataMap.Contains(ItemID))
	{
		return true;
	}

	//�������� ����
	return false;
}

FCropSheetData UNFGameInstance::GetCropDataFromSheet(const FName& CropID)
{
	//�� Crop ID
	if (CropID.IsNone())
	{
		Debug::Print(DEBUG_TEXT("Empty CropID"));
		return FCropSheetData();
	}

	//Data Table�� ���� ����
	if (!IsValid(CropSheetTable))
	{
		Debug::Print(DEBUG_TEXT("Crop Sheet Table Not Set"));
		return FCropSheetData();
	}


	//�����ϴ� �������̸� ��� ���� �� true
	FCropSheetData* cropSheetData = CropSheetTable->FindRow<FCropSheetData>(CropID, "");
	if (cropSheetData != nullptr)
	{

		return *cropSheetData;
	}

	//�������� �ʴ� ������ ����
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

	//�Ŵ��� ���� ���� �� �ʱ�ȭ
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
