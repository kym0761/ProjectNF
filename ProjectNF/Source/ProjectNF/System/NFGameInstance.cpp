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


	GridManager = CreateDefaultSubobject<UGridManager>(TEXT("GridManager"));
	ElectricLinkManager = CreateDefaultSubobject<UElectricLinkManager>(TEXT("ElectricLinkManager"));
	ObjectPoolManager = CreateDefaultSubobject<UObjectPoolManager>(TEXT("ObjectPoolManager"));
	InventoryManager = CreateDefaultSubobject<UInventoryManager>(TEXT("InventoryManager"));
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

bool UNFGameInstance::GetItemDataFromDataTable(const FName& ItemID, FItemBaseData& Out)
{

	//�� ������ ID
	if (ItemID.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty ItemID"));
		return false;
	}

	//Data Table�� ���� ����
	if (!IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Data Table Not Set"));
		return false;
	}


	//�����ϴ� �������̸� ��� ���� �� true
	FItemBaseData* itemBaseData = ItemDataTable->FindRow<FItemBaseData>(ItemID, "");
	if (itemBaseData != nullptr)
	{
		Out = *itemBaseData;
		return true;
	}

	//�������� �ʴ� ������ ����
	return false;
}

bool UNFGameInstance::IsValidItem(const FName& ItemID) const
{
	//Data Table�� ���� ����
	if (!IsValid(ItemDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Data Table Not Set"));
		return false;
	}


	//�����ϴ� �������̸� true
	FItemBaseData* itemBaseData = ItemDataTable->FindRow<FItemBaseData>(ItemID, "");
	if (itemBaseData != nullptr)
	{
		return true;
	}

	//�������� �ʴ� ������
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

	GridManager->ManagerInit();
	ElectricLinkManager->ManagerInit();
	ObjectPoolManager->ManagerInit();
	InventoryManager->ManagerInit();

	GGridManager = GridManager;
	GElectricLinkManager = ElectricLinkManager;
	GObjectPoolManager = ObjectPoolManager;
	GInventoryManager = InventoryManager;
}

void UNFGameInstance::Test()
{
	if (GEngine)
	{
		auto world = GEngine->GetCurrentPlayWorld();

		if (IsValid(world))
		{
			Debug::Print(DEBUG_TEXT("World valid."));

			UObject* outer = world;
			while (IsValid(outer))
			{
				Debug::Print(FString::Printf(TEXT(" outer : %s"), *outer->GetName()));
				outer = outer->GetOuter();
			}
		}
		else
		{
			Debug::Print(DEBUG_TEXT("World invalid."));
		}
	}
	else
	{
		Debug::Print(DEBUG_TEXT("GEngine invalid."));
	}
	
}

TObjectPtr<UGridManager> UNFGameInstance::GetGridManager()
{
	return GGridManager;
}

TObjectPtr<UElectricLinkManager> UNFGameInstance::GetElectricLinkManager()
{
	return GElectricLinkManager;
}
