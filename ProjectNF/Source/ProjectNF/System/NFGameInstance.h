// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Defines/Data.h"
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

	//player �̸�
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> CropSheetTable;

public:

	bool GetItemDataFromDataTable(const FName& ItemID, FItemSheetData& Out);
	bool IsValidItem(const FName& ItemID) const;

	bool GetCropDataFromSheet(const FName& CropID, FCropSheetData& Out);

#pragma endregion

#pragma region GameResource

protected:

	/*��ȭ���� GameInstance���� ������ �� ����.*/
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

};
