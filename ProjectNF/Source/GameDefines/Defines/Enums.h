// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#pragma region ItemEnum //������ �з�

UENUM(BlueprintType)
enum class  EItemGroupType : uint8
{
	None = 0 UMETA(DisplayName = "None"),

	/*�Ϲ� ������ �з�*/
	Equipment UMETA(DisplayName = "Equipment"),
	Consumable UMETA(DisplayName = "Consumable")

};

UENUM(BlueprintType)
enum class  EItemType : uint8
{
	None = 0 UMETA(DisplayName = "None"),

	/*��� ������ �з�*/
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory"),

	/*�Ϲ� ������ �з�*/
	Potion UMETA(DisplayName = "Potion"),
	Harvest UMETA(DisplayName = "Harvest")
	// �߰��� �� �� �ִ���?

};

UENUM(BlueprintType)
enum class  EItemSubType : uint8
{
	None = 0 UMETA(DisplayName = "None"),

	/*����*/
	Sword UMETA(DisplayName = "Weapon"),
	Dagger UMETA(DisplayName = "Dagger"),
	Bow UMETA(DisplayName = "Bow"),
	Wand UMETA(DisplayName = "Wand"),

	/*����*/
	Helmet UMETA(DisplayName = "Helmet"),
	Armor UMETA(DisplayName = "Armor"),
	Shield UMETA(DisplayName = "Shield"),
	Gloves UMETA(DisplayName = "Gloves"),
	Shoes UMETA(DisplayName = "Shoes"),

	/*�Ǽ�����*/
	Accessory UMETA(DisplayName = "Accessory"),

	/*�Ϲ� ������ �з�*/
	HealthPotion UMETA(DisplayName = "HealthPotion"),
	ManaPotion UMETA(DisplayName = "ManaPotion"),

	Harvest UMETA(DisplayName = "Harvest")
	// �߰��� �� �� �ִ���?

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
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemStar : uint8
{
	Zero UMETA(DisplayName = "0"),
	One UMETA(DisplayName = "1"),
	Two UMETA(DisplayName = "2"),
	Three UMETA(DisplayName = "3")
};

#pragma endregion

#pragma region State

//Cast���� �ʰ� ĳ���� State�� �������� �˾Ƴ��� ���� Enum
//State�� �߰��Ѵٸ� �� �߰��� �� CharacterStateType�� �ùٸ� ������ Set�� ��

UENUM(BlueprintType)
enum class  ECharacterStateType : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),

	/*�Ϲ� ������ �з�*/
	NORMAL UMETA(DisplayName = "NORMAL"),
	BATTLE UMETA(DisplayName = "BATTLE"),
	FARMING UMETA(DisplayName = "FARMING"),
	PLANTING UMETA(DisplayName = "PLANTING")
};

#pragma endregion

UENUM(BlueprintType)
enum class ELanguage : uint8
{
	Korean UMETA(DisplayName = "Korean"),
	English UMETA(DisplayName = "English")
};