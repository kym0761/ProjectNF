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

class UNFSaveGame;

/**
 * 
 */
UCLASS()
class GAMESYSTEMS_API UNFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNFGameInstance();

protected:

	//player 이름
	UPROPERTY()
	FString PlayerName;
	
	//세이브할 때 사용할 SlotNumber
	UPROPERTY()
	int32 SaveSlotNumber;

public:

	static UNFGameInstance* GetNFGameInstance();

#pragma region SaveGameFunction

public:

	UFUNCTION(BlueprintCallable)
	void Save();

	UFUNCTION(BlueprintCallable)
	void Load(int32 SlotNumber);

protected:

	void SaveInventory(UNFSaveGame* SaveGame);
	void LoadInventory(UNFSaveGame* SaveGame);

	void SaveFarmlandTile(UNFSaveGame* SaveGame);
	void LoadFarmlandTile(UNFSaveGame* SaveGame);

#pragma endregion


#pragma region Managers

protected:

	///*Manager Blueprint Classes*/

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UGridManager> GridManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UElectricLinkManager> ElectricLinkManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UObjectPoolManager> ObjectPoolManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UInventoryManager> InventoryManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UDataManager> DataManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UGameManager> GameManager_BP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UObjectManager> ObjectManager_BP;

private:

	//실제 Manager 오브젝트

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UGridManager> GridManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UElectricLinkManager> ElectricLinkManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UObjectPoolManager> ObjectPoolManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UInventoryManager> InventoryManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UDataManager> DataManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UGameManager> GameManager;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UObjectManager> ObjectManager;

private:

	//위에 Manager 멤버 변수가 있는데도 전역변수로 따로 관리하는 이유는, 
	//GameInstance의 static 함수에서 매니저의 기능을 사용할 수 있게 만들기 위함이다.

	//static TObjectPtr<UGridManager> GGridManager;
	//static TObjectPtr<UElectricLinkManager> GElectricLinkManager;
	//static TObjectPtr<UObjectPoolManager> GObjectPoolManager;
	//static TObjectPtr<UInventoryManager> GInventoryManager;
	//static TObjectPtr<UDataManager> GDataManager;
	//static TObjectPtr<UGameManager> GGameManager;
	//static TObjectPtr<UObjectManager> GObjectManager;

//protected:
//
//	//현재 필요없는 관계로 protected로 외부 사용을 막음.
//
//	static 	TObjectPtr<UGridManager> GetGridManager();
//	static 	TObjectPtr<UElectricLinkManager> GetElectricLinkManager();
//	static 	TObjectPtr<UObjectPoolManager> GetObjectPoolManager();
//	static 	TObjectPtr<UInventoryManager> GetInventoryManager();
//	static 	TObjectPtr<UDataManager> GetDataManager();
//	static 	TObjectPtr<UGameManager> GetGameManager();
//	static  TObjectPtr<UObjectManager> GetObjectManager();


	void InitManagers();
#pragma endregion

public:

	void InitNFGameInstance();


public:

	///*매니저와 관련된 Static Functions*/

	///*DataManager Functions*/
	//UFUNCTION()
	//static FItemSheetData GetItemData(const FName& ItemID);
	//
	//UFUNCTION()
	//static bool IsValidItem(const FName& ItemID);

	//UFUNCTION()
	//static FCropSheetData GetCropData(const FName& CropID);
	//
	//UFUNCTION()
	//static bool IsValidCrop(const FName& CropID);

	//UFUNCTION()
	//static FAbilitySheetData GetAbilityData(const FName& AbilityID);

	//UFUNCTION()
	//static bool IsValidAbility(const FName& AbilityID);

	//UFUNCTION()
	//static FLanguageSheetData GetLanguageData(const FName& LanguageID);
	//
	//UFUNCTION()
	//static bool IsValidLanguageData(const FName& LanguageID);


	///*Electric Link Manager*/
	//
	//UFUNCTION()
	//static void RestartLinkManager();

	///*GameManager*/
	////TODO:

	///*GridManager*/
	//UFUNCTION()
	//static FGrid WorldToGrid(const FVector& WorldLocation);

	//UFUNCTION()
	//static FVector GridToWorld(const FGrid& Grid);

	//UFUNCTION()
	//static bool IsSomethingExistOnGrid(const FGrid& Grid);

	//UFUNCTION()
	//static void SetCropMap(const TMap<FGrid, FCropData>& SavedMap);
	//
	//UFUNCTION()
	//static TMap<FGrid, FCropData>& GetCropMap();

	//UFUNCTION()
	//static void UpdateCropInfo(AFarmlandTile* TargetFarmlandTile);

	//UFUNCTION()
	//static void RemoveCropInfo(AFarmlandTile* TargetFarmlandTile);

	///*InventoryManager*/
	//UFUNCTION()
	//static UInventoryObject* TryGetInventory(FString InventoryOwner);

	//UFUNCTION()
	//static void LoadInventories(const TArray<FInventorySaveData>& InventorySaveData);

	//UFUNCTION()
	//static TMap<FString, UInventoryObject*>& GetAllInventories();

	////인벤토리에 아이템 넣기를 요청하는 기능으로, Inventory Manager에 있는 기능을 조금 추가함
	//UFUNCTION()
	//static bool AddItemToTargetInventory(AActor* InventoryOwner, const FItemSlotData& SlotData);

	///*ObjectManager*/
	//UFUNCTION()
	//static AActor* Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	//UFUNCTION()
	//static UUserWidget* CreateWidgetBlueprint(FString ToCreateWidgetName, APlayerController* WidgetOwner);

	//UFUNCTION()
	//static void Despawn(AActor* DespawnTarget);
	//
	//UFUNCTION()
	//static UNiagaraComponent* SpawnNiagaraSystem(FString ToSpawnNiagaraName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);


	///*Object Pool Manager*/

	//UFUNCTION()
	//static AActor* SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation);

	//UFUNCTION()
	//static void DespawnToPool(AActor* PoolableActor);

	//UFUNCTION()
	//static void ClearObjectPooling();

};
