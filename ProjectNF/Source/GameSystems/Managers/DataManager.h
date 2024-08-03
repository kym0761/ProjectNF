// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "Defines/Data.h"
#include "DebugHelper.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMESYSTEMS_API UDataManager : public UObject, public IManageable
{
	GENERATED_BODY()
	
public:

	UDataManager();

protected:

	/*Data Table*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> CropSheetTable;


	/*Data Cache*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TMap<FName, FItemSheetData> ItemSheetDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TMap<FName, FCropSheetData> CropSheetDataMap;


public:

	template <typename T>
	void IncludeSheetDataToMap(TMap<FName, T>& TargetDataMap, const UDataTable* SheetTable);

	//item
	bool GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out);
	bool IsValidItem(const FName& ItemID) const;

	//crop
	UFUNCTION()
	FCropSheetData GetCropDataFromSheet(const FName& CropID);

public:


	virtual void InitManager() override;
};

template<typename T>
void UDataManager::IncludeSheetDataToMap(TMap<FName, T>& TargetDataMap, const UDataTable* SheetTable)
{
	if (!IsValid(SheetTable))
	{
		Debug::Print(DEBUG_TEXT("SheetTable Not set"));
		return;
	}

	auto rowNames = SheetTable->GetRowNames();

	for (auto rowName : rowNames)
	{
		T* sheetData = SheetTable->FindRow<T>(rowName, "");
		if (!sheetData)
		{
			Debug::Print(DEBUG_TEXT("Warning! : sheet Data nullptr"));
			continue;
		}

		TargetDataMap.Add(rowName, *sheetData);
	}


	//for (auto i : TargetDataMap)
	//{
	//	FString str = FString::Printf(TEXT("key : %s"), *i.Key.ToString());

	//	Debug::Print(DEBUG_STRING(str));
	//}
}
