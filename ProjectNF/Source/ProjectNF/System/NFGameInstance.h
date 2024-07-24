// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Defines/Data.h"
#include "DebugHelper.h"
#include "NFGameInstance.generated.h"

class UInventoryObject;

class UGridManager;
class UElectricLinkManager;
class UObjectPoolManager;
class UInventoryManager;

/**
 * 
 */
UCLASS()
class PROJECTNF_API UNFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNFGameInstance();

protected:

	//player 이름
	UPROPERTY()
	FString PlayerName;
	
	//?
	UPROPERTY()
	int32 PlayerNumber;

public:

	static UNFGameInstance* GetNFGameInstance();

#pragma region SaveGameFunction

public:

	UFUNCTION()
	void Save();

	UFUNCTION()
	void Load();
#pragma endregion

#pragma region DataTables

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TMap<FName, FItemSheetData> ItemSheetDataMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> CropSheetTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TMap<FName, FCropSheetData> CropSheetDataMap;

public:

	bool GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out);
	bool IsValidItem(const FName& ItemID) const;

	UFUNCTION()
	FCropSheetData GetCropDataFromSheet(const FName& CropID);

	template <typename T>
	void IncludeSheetDataToMap(TMap<FName, T>& DataMap, const UDataTable* SheetTable);

#pragma endregion

#pragma region GameResource

protected:

	/*재화들은 GameInstance에서 관리할 수 있음.*/
	UPROPERTY()
	int32 Money;

public:

	int32 GetMoney() const;
	void AddMoney(int32 InMoney);
	bool SpendMoney(int32 Pay);

#pragma endregion


#pragma region Managers

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGridManager> GridManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UElectricLinkManager> ElectricLinkManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectPoolManager> ObjectPoolManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryManager> InventoryManager;

private:

	static TObjectPtr<UGridManager> GGridManager;
	static TObjectPtr<UElectricLinkManager> GElectricLinkManager;
	static TObjectPtr<UObjectPoolManager> GObjectPoolManager;
	static TObjectPtr<UInventoryManager> GInventoryManager;

public:

	static 	TObjectPtr<UGridManager> GetGridManager();
	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();
	static 	TObjectPtr<UObjectPoolManager> GetObjectPoolManager();
	static 	TObjectPtr<UInventoryManager> GetInventoryManager();

	void InitManagers();
#pragma endregion

public:

	void Init();

};

template<typename T>
void UNFGameInstance::IncludeSheetDataToMap(TMap<FName, T>& DataMap, const UDataTable* SheetTable)
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

		DataMap.Add(rowName, *sheetData);
	}

	for (auto i : DataMap)
	{
		FString str = FString::Printf(TEXT("key : %s"), *i.Key.ToString());

		Debug::Print(DEBUG_STRING(str));
	}
}
