// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "UObject/NoExportTypes.h"
#include "ShopObject.generated.h"

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API UShopObject : public UObject
{
	GENERATED_BODY()
	
public:

	UShopObject();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shop")
	TArray<FShopItemData> ShopItems;

};
