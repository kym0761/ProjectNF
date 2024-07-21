// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDateTime.Generated.h"

/**
 * 게임 안에서 사용할 년 월 일 시간
 * !! : 현실 시간 아님
 */


USTRUCT(BlueprintType)
struct GAMETIME_API FGameDateTime
{
	GENERATED_BODY()

public:

	//! uint32는 언리얼 에디터에서 사용할 수 없기 때문에 int32를 사용한다.

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
	/*이 부분은 되도록이면 건드리지 말 것*/

	//연도 상한치는 int32 최대값(2^31-1) -> 정상적인 플레이에서는 사실상 도달은 불가능함.
	const static int32 MAX_YEAR = TNumericLimits<int32>::Max();
	const static int32 MAX_MONTH = 12;
	const static int32 MAX_HOUR = 24;
	const static int32 MAX_MINUTE = 60;
	const static int32 MAX_WEEK = 7;

	// cpp에서 알맞는 값으로 초기화한다.
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

//월의 명칭을 관리할 데이터 테이블
USTRUCT(BlueprintType)
struct GAMETIME_API FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MonthName;
};

//계절 명칭을 관리할 데이터 테이블
USTRUCT(BlueprintType)
struct GAMETIME_API FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SeasonName;
};