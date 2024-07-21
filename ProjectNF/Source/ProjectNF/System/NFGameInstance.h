// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Item.h" //GameItem Module.
#include "NFGameInstance.generated.h"

class UInventoryObject;

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

	/*��ȭ���� GameInstance���� ������ �� ����.*/
	UPROPERTY()
	int32 Money;

public:

	int32 GetMoney() const;
	void AddMoney(int32 InMoney);
	bool SpendMoney(int32 Pay);

#pragma endregion


#pragma region GameInventory

protected:

	//key : �κ��丮 ������ , value : �κ��丮
	UPROPERTY()
	TMap<FString, TObjectPtr<UInventoryObject>> InventoryMap;

public:

	TObjectPtr<UInventoryObject> GetInventory(FString InventoryOwner);

#pragma endregion


	UFUNCTION(BlueprintCallable)
	void Test();

};
