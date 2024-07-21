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

 /*�𸮾� �����Ϳ��� �����ϱ� ���� Ŭ������ �����δ� ����ϰ� ���� ����.*/
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
struct GAMEITEM_API FShopItemData
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

//��� �������� ����
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

	//�߰� ������ �ʿ�������? --> ���� : ��� ����� �ɸ��� Buff ȿ��
};

//���� ����
USTRUCT(BlueprintType)
struct GAMEITEM_API FItemCraftData : public FTableRowBase
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