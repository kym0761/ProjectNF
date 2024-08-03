// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatAttribute.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEFINES_API UStatAttribute : public UObject
{
	GENERATED_BODY()
	
public:
	UStatAttribute();

protected:
	
	//Max
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float BaseValue;

	//Current
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float CurrentValue;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta=(AllowPrivateAccess))
	bool bIsDirty;

public:

	void InitStat(float InValue);
	void SetStat(float InValue);

	void AddMaxStat(float InValue);
	void SubtractMaxStat(float InValue);

	void AddStat(float InValue);
	void SubtractStat(float InValue);

	float GetMaxstat() const;
	float GetStat() const;

};
