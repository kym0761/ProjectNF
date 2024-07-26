// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"

UDataManager::UDataManager()
{
}

bool UDataManager::GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out)
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

bool UDataManager::IsValidItem(const FName& ItemID) const
{
	//Map에 존재하면 아이템 존재함
	if (ItemSheetDataMap.Contains(ItemID))
	{
		return true;
	}

	//존재하지 않음
	return false;
}

FCropSheetData UDataManager::GetCropDataFromSheet(const FName& CropID)
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

void UDataManager::InitManager()
{
	IncludeSheetDataToMap<FItemSheetData>(ItemSheetDataMap, ItemDataTable);
	IncludeSheetDataToMap<FCropSheetData>(CropSheetDataMap, CropSheetTable);
}
