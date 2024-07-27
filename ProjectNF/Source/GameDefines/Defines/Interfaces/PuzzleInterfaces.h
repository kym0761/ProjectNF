// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleInterfaces.generated.h"



/*
ITriggerable : Trigger 동작 인터페이스
IBeTriggerable : Trigger를 당했을 때의 동작 인터페이스
IResetable : 리셋이 가능한 대상일 때 필요한 인터페이스. ex) ResetButton
ICombustible : 불 붙는게 가능한 대상일 때 필요한 인터페이스. ex)FireBowl, FireStand
*/

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class GAMEDEFINES_API UTriggerable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEDEFINES_API ITriggerable
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Trigger() = 0;

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class GAMEDEFINES_API UBeTriggerable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEDEFINES_API IBeTriggerable
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintNativeEvent)
	virtual void BeTriggered(TObjectPtr<class APuzzleActorBase> TriggerActor, bool TriggerValue) = 0;


};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class GAMEDEFINES_API UResetable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEDEFINES_API IResetable
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Reset() = 0;

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class GAMEDEFINES_API UCombustible : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class GAMEDEFINES_API ICombustible
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Combust() = 0;

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Extinguish() = 0;

	virtual void TurnOn() = 0;
	virtual void TurnOff() = 0;

};

