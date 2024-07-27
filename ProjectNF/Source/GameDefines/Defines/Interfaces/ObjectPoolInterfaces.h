// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolInterfaces.generated.h"


 /**
  * ObjectPool이 가능하려면 IObjectPoolable을 Actor에 적용해야함.
  */

UINTERFACE(Blueprintable)
class GAMEDEFINES_API UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEDEFINES_API IObjectPoolable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PoolBeginPlay();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PoolEndPlay();

};


