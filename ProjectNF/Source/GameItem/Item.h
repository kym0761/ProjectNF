// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

//������ �з�
UENUM(BlueprintType)
enum class  EItemType : uint8
{
	None = 0 UMETA(DisplayName = "Consumable"),

	/*�Ϲ� ������ �з�*/
	Consumable UMETA(DisplayName = "Consumable"),
	Resource UMETA(DisplayName = "Resource"),
	Harvest UMETA(DisplayName = "Harvest"),

	/*��� ������ �з�*/
	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory")

};

//ComsumableItem�� ȿ�� �з�
//bitmask => 0(ignored), 1, 2, 4, 8, ..., 256(X)
UENUM(BlueprintType, Meta = (BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class  EConsumableItemType : uint8
{
	None = 0 UMETA(Hidden),

	Heal = 1 UMETA(DisplayName = "Heal"),
	Cure = 2 UMETA(DisplayName = "Cure"),
	Buff = 4 UMETA(DisplayName = "Buff"),
	Debuff = 8 UMETA(DisplayName = "Debuff"),

	X = 255 UMETA(Hidden)
};

//������ ��� ����
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None UMETA(DisplayName = "None"),

	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory")
};

UENUM(BlueprintType)
enum class  ECureType : uint8
{
	None UMETA(DisplayName = "None"),

	Poison UMETA(DisplayName = "Poison"),
	Stun UMETA(DisplayName = "Stun"),
	Iced UMETA(DisplayName = "Iced"),
	Burn UMETA(DisplayName = "Burn"),
	Sleep UMETA(DisplayName = "Sleep"),
	Blind UMETA(DisplayName = "Blind"),
	Fear UMETA(DisplayName = "Fear"),

	All UMETA(DisplayName = "All")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Rare UMETA(DisplayName = "Rare"),
	Unique UMETA(DisplayName = "Unique"),
	Epic UMETA(DisplayName = "Epic")
};

UENUM(BlueprintType)
enum class EItemStar : uint8
{
	Zero UMETA(DisplayName = "0"),
	One UMETA(DisplayName = "1"),
	Two UMETA(DisplayName = "2"),
	Three UMETA(DisplayName = "3")
};

USTRUCT(BlueprintType)
struct GAMEITEM_API FItemBaseData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//������ ���̺��� 'Row Name'�� �������� "ItemID"�� ���

	//ItemBaseData�� ItemName�� FText�� ���� Localizing�� ���� ���� �ִ� ���̴�.
	// Item ID�� �ƴ�!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;

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
		return ItemName.EqualTo(Other.ItemName);
	}

	FORCEINLINE bool operator!=(const FItemBaseData& Other)
	{
		return !(ItemName.EqualTo(Other.ItemName));
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

//���� �������� ����
USTRUCT(BlueprintType)
struct GAMEITEM_API FWeaponItemData : public FTableRowBase
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

};

//���� �������� ����
USTRUCT(BlueprintType)
struct GAMEITEM_API FShieldItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	float CriticalHit;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	//EGameGuardType GuardType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	//EGameElementType ElementType;

};

//���� �������� ������ ����
USTRUCT(BlueprintType)
struct GAMEITEM_API FArmorItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	float CriticalHit;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
	//EGameElementType ElementType;

};

//�Ǽ����� ������ ����
USTRUCT(BlueprintType)
struct GAMEITEM_API FAccessoryItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//'Row Name' Will Be "ItemID" in Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessory")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessory")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accessory")
	float CriticalHit;

	//�߰� ������ �ʿ�������? --> ���� : Buff ȿ�� �� ���������

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

	//���� ����� �Ƹ�..
	//���� ���� �ð��� ����� ��, ���� �Ϸ� �ð��� ������ ä���� �� �ְ� �ϸ� �� ��?

};