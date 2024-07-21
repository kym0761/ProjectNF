// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Item.h" //GameItem Module.
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

public:

	bool GetItemDataFromDataTable(const FName& ItemID, FItemBaseData& Out);
	bool IsValidItem(const FName& ItemID) const;

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
#pragma endregion

public:

	void InitManagers();

	UFUNCTION(BlueprintCallable)
	void Test();

public:

	static 	TObjectPtr<UGridManager> GetGridManager();
	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();

};
