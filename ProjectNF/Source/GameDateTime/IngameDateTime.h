// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IngameDateTime.Generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct GAMEDATETIME_API FIngameDateTime
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Year;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Minute;

#pragma region ConstTimeValue 
	/*�� �κ��� �ǵ����̸� �ǵ帮�� �� ��*/

	//�ִ� õ����?
	const static int32 MAX_YEAR = 10000000;
	const static int32 MAX_MONTH = 12;
	const static TArray<int32> MAXDAY_OF_MONTH; // initialized in cpp.
	const static int32 MAX_HOUR = 24;
	const static int32 MAX_MINUTE = 60;
	const static int32 MAX_WEEK = 7;

	const static FIngameDateTime MORNING;
	const static FIngameDateTime NOON;
	const static FIngameDateTime EVENING;
#pragma endregion

	FIngameDateTime(int32 InYear = 0, int32 InMonth = 0, int32 InDay = 0, int32 InHour = 0, int32 InMinute = 0);

	FIngameDateTime operator+(const FIngameDateTime& rValue);
	FIngameDateTime& operator+=(const FIngameDateTime& rValue);

	FIngameDateTime operator-(const FIngameDateTime& rValue);
	FIngameDateTime& operator-=(const FIngameDateTime& rValue);

	FString ToString();

};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MonthName;
};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SeasonName;
};