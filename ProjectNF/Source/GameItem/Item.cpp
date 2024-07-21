// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
}


FItemBaseData::FItemBaseData()
	:Thumbnail(nullptr),
	bIsStackable(true),
	MaxQuantity(1000),
	ItemType(EItemType::None),
	ItemRarity(EItemRarity::Normal),
	ItemPrice(1),
	ItemMesh(nullptr)
{

}

bool FItemBaseData::IsEmpty()
{
	//ItemBaseData의 이름의 빈 값은 아무 정보도 아닌 것으로 판정함.
	return ItemNameID.IsEmpty();
}



FItemSlotData::FItemSlotData() :ItemName("None"), Quantity(0)
{

}

bool FItemSlotData::IsSameItem(const FItemSlotData& Other) const
{
	return ItemName.IsEqual(Other.ItemName);
}

bool FItemSlotData::IsEmpty() const
{
	return ItemName.IsNone() || Quantity == 0;
}

void FItemSlotData::SetEmpty()
{
	ItemName = "None";
	Quantity = 0;
}

FShopItemData::FShopItemData()
{
	ItemName = FName(TEXT(""));
	Price = 0;
	Stock = 0;
}
