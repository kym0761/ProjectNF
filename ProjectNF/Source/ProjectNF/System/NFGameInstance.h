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
class UObjectManager;
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

protected:

	/*Blueprint Class*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGridManager> GridManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UElectricLinkManager> ElectricLinkManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UObjectPoolManager> ObjectPoolManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryManager> InventoryManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDataManager> DataManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameManager> GameManager_BP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UObjectManager> ObjectManager_BP;

protected:

	//실제 Manager 오브젝트

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectManager> ObjectManager;

private:

	//위에 Manager 변수가 있는데도 전역변수로도 관리하는 이유는, Get_Manager()를 Static 함수로 사용할 수 있게 만들기 위함이다.

	static TObjectPtr<UGridManager> GGridManager;
	static TObjectPtr<UElectricLinkManager> GElectricLinkManager;
	static TObjectPtr<UObjectPoolManager> GObjectPoolManager;
	static TObjectPtr<UInventoryManager> GInventoryManager;
	static TObjectPtr<UDataManager> GDataManager;
	static TObjectPtr<UGameManager> GGameManager;
	static TObjectPtr<UObjectManager> GObjectManager;

public:

	static 	TObjectPtr<UGridManager> GetGridManager();
	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();
	static 	TObjectPtr<UObjectPoolManager> GetObjectPoolManager();
	static 	TObjectPtr<UInventoryManager> GetInventoryManager();
	static 	TObjectPtr<UDataManager> GetDataManager();
	static 	TObjectPtr<UGameManager> GetGameManager();
	static TObjectPtr<UObjectManager> GetObjectManager();

	void InitManagers();
#pragma endregion

public:

	void InitNFGameInstance();

};
