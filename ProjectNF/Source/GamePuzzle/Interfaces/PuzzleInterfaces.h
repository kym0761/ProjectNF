// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleInterfaces.generated.h"

/*
ITriggerable : Trigger ���� �������̽�
IBeTriggerable : Trigger�� ������ ���� ���� �������̽�
IResetable : ������ ������ ����� �� �ʿ��� �������̽�. ex) ResetButtonTrigger
ICombustible : �� �ٴ°� ������ ����� �� �ʿ��� �������̽�. ex)FireTorch, FireStand
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

	UFUNCTION(BlueprintNativeEvent, Category = "Trigger")
	void Trigger();

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

	UFUNCTION(BlueprintNativeEvent, Category = "Trigger")
	void BeTriggered();

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

	UFUNCTION(BlueprintNativeEvent, Category = "reset")
	void Reset();

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

	UFUNCTION(BlueprintNativeEvent, Category = "Combust")
	void Combust();

	UFUNCTION(BlueprintNativeEvent, Category = "Combust")
	void Extinguish();

	virtual void TurnOn() = 0;
	virtual void TurnOff() = 0;

};
