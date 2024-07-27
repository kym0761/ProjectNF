// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerInterfaces.generated.h"




//Interactive Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UManageable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interactive Interface Class. You must Use This When you Inherit Interface.
class IManageable
{
	GENERATED_BODY()

public:


	virtual void InitManager() = 0;

};