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

TObjectPtr<UInventoryObject> UNFGameInstance::GetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//잘못된 인벤토리 접근법
		return nullptr;
	}

	//TODO : 인벤토리 Owner 자체가 존재하는지부터..
	if (!InventoryMap.Contains(InventoryOwner))
	{
		//TODO : 인벤토리 생성시, 지정된 크기 등으로 초기화? 
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
