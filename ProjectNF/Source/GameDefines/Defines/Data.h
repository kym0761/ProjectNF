// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Data.Generated.h"

/**
 * Ȥ�� �𸮾� �ҽ��� ���𰡿� �浹�Ǹ� GameData��� ��Ī �ٲ� �� ������;
 */

#pragma region ItemData

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FItemSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//������ ���̺��� 'Row Name'�� �������� "ItemID"�� ���

	//ItemName������ Localize������ ���̺��� �˻��� Korean ����� Kor �����͸� �����´�..


	//ItemBaseData�� ItemName�� FText�� ���� Localizing�� ���� ���� �ִ� ���̴�.
	// Item ID�� �ƴ�!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemNameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText DescriptionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemGroupType ItemGroupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemSubType ItemSubType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemStar ItemStar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> ItemMesh;

	FItemSheetData();

	FORCEINLINE bool operator==(const FItemSheetData& Other)
	{
		return ItemNameID.EqualTo(Other.ItemNameID);
	}

	FORCEINLINE bool operator!=(const FItemSheetData& Other)
	{
		return !(ItemNameID.EqualTo(Other.ItemNameID));
	}

	bool IsEmpty();

};

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FItemSlotData
{
	GENERATED_BODY()

public:

	//DataTable�� �˻��� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	// potential TODO : SlotData�� ��� �������� ���� ������ ���� �� �ְ� �߰��� �ʿ䰡 ���� ���� ����.

	FItemSlotData();
	//FItemSlotData(const FItemBaseData& ItemData, int32 Num);

	FORCEINLINE bool operator==(const FItemSlotData& Other)
	{
		return ItemName.IsEqual(Other.ItemName);
	}
	FORCEINLINE bool operator!=(const FItemSlotData& Other)
	{
		return !(ItemName == Other.ItemName);
	}

	bool IsSameItem(const FItemSlotData& Other) const;
	bool IsEmpty() const;

	void SetEmpty();
};

//ItemShop���� ����� ����ü
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FShopItemData
{
	GENERATED_BODY()

public:

	//DataTable�� �˻��� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Stock;

	FShopItemData();
	//FShopItemData(const FItemBaseData& ItemData, int32 Num);

};

//Consumable ������ ����
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FConsumableItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable", Meta = (BitMask, BitMaskEnum = EConsumableItemType))
	int32 ConsumableItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float AddHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float AddMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	float AddStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
	ECureType CureType;

};

//��� �������� ����
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FEquipmentItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float CriticalHit;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//EGameAttackType AttackType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//EGameAttackRangeType AttackRangeType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//EGameElementType ElementType;

	//�߰� ������ �ʿ�������? --> ���� : ��� ����� �ɸ��� Buff ȿ��
};

//���� ����
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FItemCraftData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	//�����ϸ� ������ ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	//�ʿ��� ������ ���� (ResourceItemName, ResourceQuantity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FName, int32> Resources;

	//�����ϴµ� �ʿ��� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float LeadTime;

	//���� ����� ������ ���̵� �ʿ�
	// ���� ���̵�� : ���� start �ð��� ����� ��, ���� completed �ð��� ������ �������� ���� �� �ְ� �ϸ� �� ��?

};

#pragma endregion

#pragma region Grid

/**
 * FVector�� ǥ���� ��ġ�� int , int ������ �׸���� ǥ���ϴ� ���� ����ü
 */
USTRUCT(BlueprintType, Blueprintable)
struct GAMEDEFINES_API FGrid
{
	GENERATED_BODY()

	//����ü _API ��� ���ϰ� ����ϸ� ���� ��⿡�� ���� ���� �߻���.

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Y;

	FGrid();
	FGrid(int32 _X, int32 _Y);
	FString ToString() const;
	bool operator==(const FGrid& Other) const;
	bool operator!= (const FGrid& Other) const;
	FGrid operator+(const FGrid& b) const;
	FGrid operator-(const FGrid& b) const;
	FGrid& operator=(const FGrid& b);
	FGrid& operator+=(const FGrid& b);
	FGrid& operator-=(const FGrid& b);
	int32 Size() const;

	bool IsInvalidGrid() const;
};

//�ܺ� ��⿡�� �� Hash�� ����Ƿ��� GAMEFARM_API�� �Լ� �տ� �پ���ϴ� ������ ����.
//hash : TSet, TMap..
GAMEDEFINES_API uint32 GetTypeHash(const FGrid& Grid);

#pragma endregion

#pragma region GameTime

/**
 * ���� �ȿ��� ����� �� �� �� �ð�
 * !! : ���� �ð� �ƴ�
 */


USTRUCT(BlueprintType)
struct GAMEDEFINES_API FGameDateTime
{
	GENERATED_BODY()

public:

	//! uint32�� �𸮾� �����Ϳ��� ����� �� ���� ������ int32�� ����Ѵ�.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Year;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Minute;

#pragma region ConstTimeValue 	/*�� �κ��� �ǵ����̸� �ǵ帮�� �� ��*/

	//���� ����ġ�� int32 �ִ밪(2^31-1) -> �������� �÷��̿����� ��ǻ� ������ �Ұ�����.
	const static int32 MAX_YEAR = TNumericLimits<int32>::Max();
	const static int32 MAX_MONTH = 12;
	const static int32 MAX_HOUR = 24;
	const static int32 MAX_MINUTE = 60;
	const static int32 MAX_WEEK = 7;

	// cpp���� �˸´� ������ �ʱ�ȭ�Ѵ�.
	const static TArray<int32> MAXDAY_OF_MONTH;
	const static FGameDateTime MORNING;
	const static FGameDateTime NOON;
	const static FGameDateTime EVENING;
#pragma endregion

	FGameDateTime(int32 InYear = 0, int32 InMonth = 0, int32 InDay = 0, int32 InHour = 0, int32 InMinute = 0);

	FGameDateTime operator+(const FGameDateTime& rValue);
	FGameDateTime& operator+=(const FGameDateTime& rValue);

	FGameDateTime operator-(const FGameDateTime& rValue);
	FGameDateTime& operator-=(const FGameDateTime& rValue);

	FString ToString() const;

};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MonthName;
};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SeasonName;
};

#pragma endregion

#pragma region Farming 


USTRUCT(BlueprintType)
struct GAMEDEFINES_API FCropSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//������ ���̺� Row name���� ������ ������.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FText CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 MaxGrowth;

	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh0;

	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh1;

	//�߰� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh2;

	//�� �ڶ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh3;

	FCropSheetData();

	FORCEINLINE bool operator==(const FCropSheetData& Other)
	{
		return CropName.EqualTo(Other.CropName);
		//return CropName == Other.CropName;
	}

	FORCEINLINE bool operator!=(const FCropSheetData& Other)
	{
		return !(CropName.EqualTo(Other.CropName));
		//return CropName != Other.CropName;
	}

	bool IsEmpty();

};

//FarmlandTile�� �� Crop ���� 
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FCropData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FName CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	bool bWatered;

};

//SaveGame�� ����� ���̺�� ����ü
//Grid ��ġ���� �����Ͽ� load�ϰ� farm�ʿ��� Grid��ġ�� �°� ��ġ�� �뵵
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FFarmlandSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FName CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FGrid Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	bool bWatered;

};

#pragma endregion