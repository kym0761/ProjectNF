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
class UDataManager;

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

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UGridManager> GridManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UElectricLinkManager> ElectricLinkManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UObjectPoolManager> ObjectPoolManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UInventoryManager> InventoryManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UDataManager> DataManager_BP;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGridManager> GridManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UElectricLinkManager> ElectricLinkManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectPoolManager> ObjectPoolManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryManager> InventoryManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataManager> DataManager;

private:

	static TObjectPtr<UGridManager> GGridManager;
	static TObjectPtr<UElectricLinkManager> GElectricLinkManager;
	static TObjectPtr<UObjectPoolManager> GObjectPoolManager;
	static TObjectPtr<UInventoryManager> GInventoryManager;
	static TObjectPtr<UDataManager> GDataManager;
public:

	static 	TObjectPtr<UGridManager> GetGridManager();
	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();
	static 	TObjectPtr<UObjectPoolManager> GetObjectPoolManager();
	static 	TObjectPtr<UInventoryManager> GetInventoryManager();
	static 	TObjectPtr<UDataManager> GetDataManager();

	void InitManagers();
#pragma endregion

public:

	void Init();

};
