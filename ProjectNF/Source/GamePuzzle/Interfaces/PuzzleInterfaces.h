// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleInterfaces.generated.h"

/*
ITriggerable : Trigger ���� �������̽�
IBeTriggerable : Trigger�� ������ ���� ���� �������̽�
IResetable : ������ ������ ����� �� �ʿ��� �������̽�. ex) ResetButton
ICombustible : �� �ٴ°� ������ ����� �� �ʿ��� �������̽�. ex)FireBowl, FireStand
*/

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UTriggerable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class ITriggerable
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Trigger() = 0;

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UBeTriggerable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class IBeTriggerable
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintNativeEvent)
	virtual void BeTriggered(TObjectPtr<class APuzzleActorBase> TriggerActor, bool TriggerValue) = 0;


};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UResetable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class IResetable
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	virtual void Reset() = 0;

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UCombustible : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class ICombustible
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
