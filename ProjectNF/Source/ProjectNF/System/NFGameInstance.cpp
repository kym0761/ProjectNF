// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameInstance.h"
#include "NFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryObject.h"
#include "DebugHelper.h"

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

TObjectPtr<UInventoryObject> UNFGameInstance::GetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//�߸��� �κ��丮 ���ٹ�
		return nullptr;
	}

	//TODO : �κ��丮 Owner ��ü�� �����ϴ�������..
	if (!InventoryMap.Contains(InventoryOwner))
	{
		//TODO : �κ��丮 ������, ������ ũ�� ������ �ʱ�ȭ? 
		UInventoryObject* inventory = NewObject<UInventoryObject>(this);
		inventory->InitInventory();

		InventoryMap[InventoryOwner] = inventory;
	}


	return InventoryMap[InventoryOwner];
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
