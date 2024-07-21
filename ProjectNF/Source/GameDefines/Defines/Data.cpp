// Fill out your copyright notice in the Description page of Project Settings.


#include "Data.h"

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

//~~

FGrid::FGrid()
{
	X = 0;
	Y = 0;
}

FGrid::FGrid(int32 _X, int32 _Y)
{
	X = _X;
	Y = _Y;
}

FString FGrid::ToString() const
{
	return FString("X : ") + FString::FromInt(X) + FString(" / Y : ") + FString::FromInt(Y);
}

bool FGrid::operator==(const FGrid& Other) const
{
	return X == Other.X && Y == Other.Y;
}

bool FGrid::operator!=(const FGrid& Other) const
{
	return !(*this == Other);
}

FGrid FGrid::operator+(const FGrid& b) const
{
	FGrid temp;
	temp.X = X + b.X;
	temp.Y = Y + b.Y;
	return temp;
}

FGrid FGrid::operator -(const FGrid& b) const
{
	FGrid temp;
	temp.X = X - b.X;
	temp.Y = Y - b.Y;
	return temp;
}

FGrid& FGrid::operator=(const FGrid& b)
{
	X = b.X;
	Y = b.Y;

	return *this;
}

FGrid& FGrid::operator+=(const FGrid& b)
{
	(*this) = (*this) + b;
	return *this;
}

FGrid& FGrid::operator-=(const FGrid& b)
{
	(*this) = (*this) - b;
	return *this;
}

int32 FGrid::Size() const
{
	return FMath::Abs(X) + FMath::Abs(Y);
}

bool FGrid::IsInvalidGrid() const
{
	return X < 0 || Y < 0;
}

uint32 GetTypeHash(const FGrid& Grid)
{
	return FCrc::MemCrc32(&Grid, sizeof(Grid));
}