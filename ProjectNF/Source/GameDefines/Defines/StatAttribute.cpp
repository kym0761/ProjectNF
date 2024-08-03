// Fill out your copyright notice in the Description page of Project Settings.


#include "StatAttribute.h"

UStatAttribute::UStatAttribute()
{
	BaseValue = 100;
	CurrentValue = 100;
	bIsDirty = false;
}

void UStatAttribute::InitStat(float InValue)
{
	BaseValue = InValue;
	CurrentValue = InValue;
	bIsDirty = false;
}

void UStatAttribute::SetStat(float InValue)
{
	BaseValue = InValue;
	CurrentValue = InValue;
	bIsDirty = true;
}

void UStatAttribute::AddMaxStat(float InValue)
{
	BaseValue += InValue;
	CurrentValue = FMath::Clamp(CurrentValue, 0, BaseValue);
	bIsDirty = true;
}

void UStatAttribute::SubtractMaxStat(float InValue)
{
	BaseValue -= InValue;
	CurrentValue = FMath::Clamp(CurrentValue, 0, BaseValue);
	bIsDirty = true;
}

void UStatAttribute::AddStat(float InValue)
{
	CurrentValue = FMath::Clamp(CurrentValue + InValue, 0, BaseValue);
	bIsDirty = true;
}

void UStatAttribute::SubtractStat(float InValue)
{
	CurrentValue = FMath::Clamp(CurrentValue - InValue, 0, BaseValue);
	bIsDirty = true;
}

float UStatAttribute::GetMaxstat() const
{
	return BaseValue;
}

float UStatAttribute::GetStat() const
{
	return CurrentValue;
}
