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
class UGameManager;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers")
	TSubclassOf<UGameManager> GameManager_BP;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGameManager> GameManager;
private:

	static TObjectPtr<UGridManager> GGridManager;
	static TObjectPtr<UElectricLinkManager> GElectricLinkManager;
	static TObjectPtr<UObjectPoolManager> GObjectPoolManager;
	static TObjectPtr<UInventoryManager> GInventoryManager;
	static TObjectPtr<UDataManager> GDataManager;
	static TObjectPtr<UGameManager> GGameManager;
public:

	static 	TObjectPtr<UGridManager> GetGridManager();
	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();
	static 	TObjectPtr<UObjectPoolManager> GetObjectPoolManager();
	static 	TObjectPtr<UInventoryManager> GetInventoryManager();
	static 	TObjectPtr<UDataManager> GetDataManager();
	static 	TObjectPtr<UGameManager> GetGameManager();

	void InitManagers();
#pragma endregion

public:

	void InitNFGameInstance();

};
