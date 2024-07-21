// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDateTime.Generated.h"

/**
 * ���� �ȿ��� ����� �� �� �� �ð�
 * !! : ���� �ð� �ƴ�
 */


USTRUCT(BlueprintType)
struct GAMETIME_API FGameDateTime
{
	GENERATED_BODY()

public:

	//! uint32�� �𸮾� �����Ϳ��� ����� �� ���� ������ int32�� ����Ѵ�.

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

	//���� ����ġ�� int32 �ִ밪(2^31-1) -> �������� �÷��̿����� ��ǻ� ������ �Ұ�����.
	const static int32 MAX_YEAR = TNumericLimits<int32>::Max();
	const static int32 MAX_MONTH = 12;
	const static int32 MAX_HOUR = 24;
	const static int32 MAX_MINUTE = 60;
	const static int32 MAX_WEEK = 7;

	// cpp���� �˸´� ������ �ʱ�ȭ�Ѵ�.
	const static TArray<int32> MAXDAY_OF_MONTH;
	const static FGameDateTime MORNING;
	const static FGameDateTime NOON;
	const static FGameDateTime EVENING;
#pragma endregion

	FGameDateTime(int32 InYear = 0, int32 InMonth = 0, int32 InDay = 0, int32 InHour = 0, int32 InMinute = 0);

	FGameDateTime operator+(const FGameDateTime& rValue);
	FGameDateTime& operator+=(const FGameDateTime& rValue);

	FGameDateTime operator-(const FGameDateTime& rValue);
	FGameDateTime& operator-=(const FGameDateTime& rValue);

	FString ToString() const;

};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct GAMETIME_API FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MonthName;
};

//���� ��Ī�� ������ ������ ���̺�
USTRUCT(BlueprintType)
struct GAMETIME_API FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SeasonName;
};