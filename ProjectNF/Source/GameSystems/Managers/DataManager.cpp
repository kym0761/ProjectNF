// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
UDataManager::UDataManager()
{
}

FItemSheetData UDataManager::GetItemData(const FName& ItemID)
{
	//빈 아이템 ID
	if (ItemID.IsNone())
	{
		//FMyDebug::Print(DEBUG_TEXT("Empty ItemID"));
		return FItemSheetData();
	}

	//존재하지 않는 아이템 데이터
	if (!ItemSheetDataMap.Contains(ItemID))
	{
		//FMyDebug::Print(DEBUG_TEXT("Invalid Item ID"));
		return FItemSheetData();
	}

	return ItemSheetDataMap[ItemID];
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

FCropSheetData UDataManager::GetCropData(const FName& CropID)
{
	//빈 작물 ID
	if (CropID.IsNone())
	{
		FMyDebug::Print(DEBUG_TEXT("Empty CropID"));
		return FCropSheetData();
	}

	//존재하지 않는 아이템 데이터
	if (!CropSheetDataMap.Contains(CropID))
	{
		FMyDebug::Print(DEBUG_TEXT("Invalid Crop ID"));
		return FCropSheetData();
	}

	return CropSheetDataMap[CropID];
}

bool UDataManager::IsValidCrop(const FName& CropID) const
{
	//Map에 존재하면 작물 존재함
	if (CropSheetDataMap.Contains(CropID))
	{
		return true;
	}

	//존재하지 않음
	return false;
}

FAbilitySheetData UDataManager::GetAbilityData(const FName& AbilityID)
{
	//빈 Ability ID
	if (AbilityID.IsNone())
	{
		FMyDebug::Print(DEBUG_TEXT("Empty AbilityID"));
		return FAbilitySheetData();
	}

	//존재하지 않는 어빌리티 데이터
	if (!AbilitySheetDataMap.Contains(AbilityID))
	{
		FMyDebug::Print(DEBUG_TEXT("Invalid AbilityID"));
		return FAbilitySheetData();
	}

	return AbilitySheetDataMap[AbilityID];
}

bool UDataManager::IsValidAbility(const FName& AbilityID) const
{
	//Map에 존재하면 어빌리티가 존재함
	if (AbilitySheetDataMap.Contains(AbilityID))
	{
		return true;
	}

	//존재하지 않음
	return false;
}

FLanguageSheetData UDataManager::GetLanguageData(const FName& LanguageID)
{
	//빈 작물 ID
	if (LanguageID.IsNone())
	{
		FMyDebug::Print(DEBUG_TEXT("Empty LanguageID"));
		return FLanguageSheetData();
	}

	//존재하지 않는 아이템 데이터
	if (!LanguageSheetDataMap.Contains(LanguageID))
	{
		FMyDebug::Print(DEBUG_TEXT("Invalid LanguageID"));
		return FLanguageSheetData();
	}

	return LanguageSheetDataMap[LanguageID];
}

bool UDataManager::IsValidLanguageData(const FName& LanguageID) const
{
	//Map에 존재하면 단어에 맞게 정의한 데이터들이 존재함
	if (LanguageSheetDataMap.Contains(LanguageID))
	{
		return true;
	}

	//존재하지 않음
	return false;
}

void UDataManager::InitManager()
{
	TArray<FName> itemDataTablePath;
	itemDataTablePath.Add(TEXT("/Game/DataTables/ItemDataTables"));
	LoadDataTables(ItemDataTables, itemDataTablePath);

	TArray<FName> cropDataTablePath;
	cropDataTablePath.Add(TEXT("/Game/DataTables/CropDataTables"));
	LoadDataTables(CropSheetTables, cropDataTablePath);

	TArray<FName> abilityDataTablePath;
	abilityDataTablePath.Add(TEXT("/Game/DataTables/AbilityDataTables"));
	LoadDataTables(AbilitySheetTables, abilityDataTablePath);

	TArray<FName> languageDataTablePath;
	languageDataTablePath.Add(TEXT("/Game/DataTables/LanguageDataTables"));
	LoadDataTables(LanguageSheetTables, languageDataTablePath);


	IncludeSheetDataToMap<FItemSheetData>(ItemSheetDataMap, ItemDataTables);
	IncludeSheetDataToMap<FCropSheetData>(CropSheetDataMap, CropSheetTables);
	IncludeSheetDataToMap<FAbilitySheetData>(AbilitySheetDataMap, AbilitySheetTables);
	IncludeSheetDataToMap<FLanguageSheetData>(LanguageSheetDataMap, LanguageSheetTables);
}

void UDataManager::LoadDataTables(TArray<TObjectPtr<UDataTable>>& TargetDataTables, const TArray<FName>& FolderPaths)
{
	FAssetRegistryModule& assetRegistryModule
		= FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TargetDataTables.Empty();

	TArray<FAssetData> assetData;

	FARFilter filter; //5.4부터인가 클래스 필터 처리가 사라짐 ㅡ,ㅡ;

	filter.bRecursivePaths = true; //폴더 recursive 옵션
	filter.PackagePaths = FolderPaths; //긁을 target이 되는 폴더

	assetRegistryModule.Get().GetAssets(filter, assetData);

	for (auto asset : assetData)
	{
		FString name = asset.GetAsset()->GetName();
		FString path = asset.GetObjectPathString();

		UDataTable* findClass = LoadObject<UDataTable>(nullptr, *path);

		//찾은 클래스가 유효한지 확인
		if (IsValid(findClass))
		{
			TargetDataTables.Add(findClass);
		}
	}

	FMyDebug::Print(DEBUG_VATEXT(TEXT("num of targetDataTable Array : %d"), TargetDataTables.Num()));

}
