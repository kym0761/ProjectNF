// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolInterface.generated.h"

/**
 * Pool 가능하려면 IObjectPoolable을 Actor에 적용해야함.
 */

UINTERFACE(Blueprintable)
class GAMEOBJECTPOOL_API UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEOBJECTPOOL_API IObjectPoolable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void PoolBeginPlay();

};