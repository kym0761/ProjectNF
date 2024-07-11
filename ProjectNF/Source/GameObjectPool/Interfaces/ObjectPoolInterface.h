// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolInterface.generated.h"

/**
 * Pool �����Ϸ��� IObjectPoolable�� Actor�� �����ؾ���.
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