// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractiveInterfaces.generated.h"


//Interactive Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

//Interactive 인터페이스, Interact 행동이 가능한 Actor들에게 넣음.
//예시) ItemPickup은 Interact에서 플레이어의 인벤토리에 접근해 아이템을 넣어주고 Destroy함.
class IInteractive
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Interactive")
	void Interact(APawn* InteractCauser);

};
