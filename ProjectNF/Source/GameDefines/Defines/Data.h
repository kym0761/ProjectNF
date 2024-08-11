// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Enums.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Data.Generated.h"

/**
 * 혹시 언리얼 소스의 무언가와 충돌되면 GameData라고 명칭 바꿀 것 ㅇㅅㅇ;
 */

#pragma region ItemData

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FItemSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//데이터 테이블의 'Row Name'이 아이템의 "ItemID"로 취급

	//TODO : 번역용 기능 만들기
	//ItemName값으로 Localize데이터 테이블을 검색해 Korean 언어라면 Kor 데이터를 가져온다..


	//ItemBaseData의 ItemName은 FText로 추후 Localizing에 사용될 수도 있는 값이다.
	// Item ID가 아님!
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

	//DataTable을 검색할 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	// potential TODO : SlotData에 장비 내구도와 같은 정보를 넣을 수 있게 추가할 필요가 있을 수도 있음.

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

//ItemShop에서 사용할 구조체
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FShopItemData
{
	GENERATED_BODY()

public:

	//DataTable을 검색할 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Stock;

	FShopItemData();
	//FShopItemData(const FItemBaseData& ItemData, int32 Num);

};

//Consumable 아이템 정보
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FConsumableItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
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

//장비 아이템의 정보
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

	//추가 정보가 필요할지도? --> 예시 : 장비 착용시 걸리는 Buff 효과
};

//제작 정보
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FItemCraftData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	//제작하면 나오는 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	//필요한 아이템 정보 (ResourceItemName, ResourceQuantity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FName, int32> Resources;

	//제작하는데 필요한 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float LeadTime;

	//제작 기능을 개선할 아이디어가 필요
	// 개선 아이디어 : 제작 start 시간을 등록한 뒤, 제작 completed 시간이 지나면 아이템을 얻을 수 있게 하면 될 듯?

};

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FInventorySaveData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	FString InventoryID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FItemSlotData> Items;
};


#pragma endregion

#pragma region Grid

/**
 * FVector로 표현된 위치를 int , int 형식의 그리드로 표현하는 정보 구조체
 */
USTRUCT(BlueprintType, Blueprintable)
struct GAMEDEFINES_API FGrid
{
	GENERATED_BODY()

	//구조체 _API 명시 안하고 사용하면 메인 모듈에서 사용시 버그 발생함.

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

//외부 모듈에서 이 Hash가 적용되려면 GAMEFARM_API가 함수 앞에 붙어야하는 것으로 보임.
//hash : TSet, TMap..
GAMEDEFINES_API uint32 GetTypeHash(const FGrid& Grid);

#pragma endregion

#pragma region GameTime

/**
 * 게임 안에서 사용할 년 월 일 시간
 * !! : 현실 시간 아님
 */


USTRUCT(BlueprintType)
struct GAMEDEFINES_API FGameDateTime
{
	GENERATED_BODY()

public:

	//! uint32는 언리얼 에디터에서 사용할 수 없기 때문에 int32를 사용한다.

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

#pragma region ConstTimeValue 	/*이 부분은 되도록이면 건드리지 말 것*/

	//연도 상한치는 int32 최대값(2^31-1) -> 정상적인 플레이에서는 사실상 도달은 불가능함.
	const static int32 MAX_YEAR = TNumericLimits<int32>::Max();
	const static int32 MAX_MONTH = 12;
	const static int32 MAX_HOUR = 24;
	const static int32 MAX_MINUTE = 60;
	const static int32 MAX_WEEK = 7;

	// cpp에서 알맞는 값으로 초기화한다.
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

	//!! : 게임속의 Year Month Day는 0이 될 수 없는 값이라는 가정하에 비교 연산자를 만들어야함.

	bool operator>(const FGameDateTime& Other) const;
	bool operator>=(const FGameDateTime& Other) const;
	bool operator<(const FGameDateTime& Other) const;
	bool operator<=(const FGameDateTime& Other) const;

	FString ToString() const;

};

//월의 명칭을 관리할 데이터 테이블
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MonthName;
};

//계절 명칭을 관리할 데이터 테이블
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SeasonName;
};

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FNPCScheduleSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FString ScheduleOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	int32 Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FGameDateTime StartDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FGameDateTime ScheduleExpireDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FString Destination;

	//해당 스케쥴에 대한 설명을 적을 공간. 딱히 기능은 없다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FString Comment;

};


USTRUCT(BlueprintType)
struct GAMEDEFINES_API FNPCScheduleActionData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	int32 Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FGameDateTime StartDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FGameDateTime ScheduleExpireDateTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FString Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	bool bCompleted;

};

#pragma endregion

#pragma region Farming 


USTRUCT(BlueprintType)
struct GAMEDEFINES_API FCropSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//데이터 테이블 Row name으로 구분할 예정임.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FText CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 MaxGrowth;

	//씨앗 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh0;

	//새싹 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh1;

	//중간 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> Mesh2;

	//다 자란 상태
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

//FarmlandTile에 들어갈 Crop 정보 
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

//SaveGame에 사용할 세이브용 구조체
//Grid 위치값을 저장하여 load하고 farm맵에서 Grid위치에 맞게 배치할 용도
USTRUCT(BlueprintType)
struct GAMEDEFINES_API FCropSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CropSave")
	FCropData CropData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CropSave")
	FGrid GridPosition;

};

#pragma endregion

#pragma region Languages

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FLanguageSheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//데이터 테이블의 'Row Name'이 "ID"로 취급

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
	FText Eng;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
	FText Kor;

	//필요에 따라 추가될 수도 있음.

};

#pragma endregion

#pragma region Ability

USTRUCT(BlueprintType)
struct GAMEDEFINES_API FAbilitySheetData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//데이터 테이블의 'Row Name'이 "ID"로 취급

	//이 어빌리티에 의해 발동할 Niagara 명칭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FString AbilityNiagara;

	//이 어빌리티에 의해 추가로 걸릴 어빌리티의 종류 명칭
	//예시) 힐을 받고나서 공격력 업!
	//예시) 공격을 받고나서 독 데미지 디버프
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<FString> AddtionalAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float HealHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float HealMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float AttackUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float DefenceUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Damage;

	//필요에 따라 추가될 수도 있음.

};

#pragma endregion