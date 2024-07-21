// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */

 /*언리얼 에디터에서 접근하기 위한 클래스로 실제로는 사용하고 있지 않음.*/
UCLASS()
class GAMEITEM_API UItem : public UObject
{
	GENERATED_BODY()
	
	UItem();
};


USTRUCT(BlueprintType)
struct GAMEITEM_API FItemBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//데이터 테이블의 'Row Name'이 아이템의 "ItemID"로 취급

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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	//	TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemStar ItemStar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMesh> ItemMesh;

	FItemBaseData();

	FORCEINLINE bool operator==(const FItemBaseData& Other)
	{
		return ItemNameID.EqualTo(Other.ItemNameID);
	}

	FORCEINLINE bool operator!=(const FItemBaseData& Other)
	{
		return !(ItemNameID.EqualTo(Other.ItemNameID));
	}

	bool IsEmpty();

};

USTRUCT(BlueprintType)
struct GAMEITEM_API FItemSlotData
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
struct GAMEITEM_API FShopItemData
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
struct GAMEITEM_API FConsumableItemData : public FTableRowBase
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

//장비 아이템의 정보
USTRUCT(BlueprintType)
struct GAMEITEM_API FEquipmentItemData : public FTableRowBase
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
struct GAMEITEM_API FItemCraftData : public FTableRowBase
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