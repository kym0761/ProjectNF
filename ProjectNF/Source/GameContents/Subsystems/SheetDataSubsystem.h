// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "DebugHelper.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SheetDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API USheetDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	USheetDataSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:

	/*Data Table*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataTable", Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UDataTable>> ItemDataTables;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataTable", Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UDataTable>> CropSheetTables;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataTable", Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UDataTable>> AbilitySheetTables;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataTable", Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UDataTable>> LanguageSheetTables;

	/*Data Cache*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataMap", Meta = (AllowPrivateAccess = true))
	TMap<FName, FItemSheetData> ItemSheetDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataMap", Meta = (AllowPrivateAccess = true))
	TMap<FName, FCropSheetData> CropSheetDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataMap", Meta = (AllowPrivateAccess = true))
	TMap<FName, FAbilitySheetData> AbilitySheetDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data|DataMap", Meta = (AllowPrivateAccess = true))
	TMap<FName, FLanguageSheetData> LanguageSheetDataMap;

protected:

	//데이터 테이블 -> 구조체에 맞는 Map으로
	template <typename T>
	void IncludeSheetDataToMap(TMap<FName, T>& TargetDataMap,
		TArray<TObjectPtr<UDataTable>> SheetTables);

	void LoadDataTables(TArray<TObjectPtr<UDataTable>>& TargetDataTables, const TArray<FName>& FolderPaths);

public:

	//item
	UFUNCTION()
	FItemSheetData GetItemData(const FName& ItemID);
	bool IsValidItem(const FName& ItemID) const;

	//crop
	UFUNCTION()
	FCropSheetData GetCropData(const FName& CropID);
	bool IsValidCrop(const FName& CropID) const;

	//crop
	UFUNCTION()
	FAbilitySheetData GetAbilityData(const FName& AbilityID);
	bool IsValidAbility(const FName& AbilityID) const;

	//Language
	UFUNCTION()
	FLanguageSheetData GetLanguageData(const FName& LanguageID);
	bool IsValidLanguageData(const FName& LanguageID) const;

};

template<typename T>
void USheetDataSubsystem::IncludeSheetDataToMap(TMap<FName, T>& TargetDataMap, TArray<TObjectPtr<UDataTable>> SheetTables)
{
	if (SheetTables.Num() == 0)
	{
		FMyDebug::Print(DEBUG_TEXT("No SheetTable"));
		return;
	}

	for (auto& sheetTable : SheetTables)
	{

		if (!IsValid(sheetTable))
		{
			FMyDebug::Print(DEBUG_TEXT("sheetTable is Invalid."));
			return;
		}

		auto rowNames = sheetTable->GetRowNames();

		//FMyDebug::Print(DEBUG_VATEXT(TEXT("rowNames num : %d"), rowNames.Num()));

		for (auto rowName : rowNames)
		{
			T* sheetData = sheetTable->FindRow<T>(rowName, "");
			if (!sheetData)
			{
				FMyDebug::Print(DEBUG_TEXT("Warning! : sheet Data nullptr"));
				continue;
			}

			TargetDataMap.Add(rowName, *sheetData);
		}

	}
}
