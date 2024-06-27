// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameDateTime.h"

//[0] 번째는 사용하지 않는다.
const TArray<int> FIngameDateTime::MAXDAY_OF_MONTH = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const FIngameDateTime FIngameDateTime::MORNING = FIngameDateTime(0, 0, 0, 6, 0);
const FIngameDateTime FIngameDateTime::NOON = FIngameDateTime(0, 0, 0, 12, 0);
const FIngameDateTime FIngameDateTime::EVENING = FIngameDateTime(0, 0, 0, 18, 0);

FIngameDateTime::FIngameDateTime(int32 InYear, int32 InMonth, int32 InDay, int32 InHour, int32 InMinute)
{
	Year = FMath::Clamp(InYear, 0, MAX_YEAR);
	Month = FMath::Clamp(InMonth, 0, MAX_MONTH);
	Day = FMath::Clamp(InDay, 0, MAXDAY_OF_MONTH[InMonth]);
	Hour = FMath::Clamp(InHour, 0, MAX_HOUR - 1);
	Minute = FMath::Clamp(InMinute, 0, MAX_MINUTE - 1);
}

FIngameDateTime FIngameDateTime::operator+(const FIngameDateTime& rValue)
{
	int32 year = this->Year + rValue.Year;
	int32 month = this->Month + rValue.Month;
	int32 day = this->Day + rValue.Day;
	int32 hour = this->Hour + rValue.Hour;
	int32 minute = this->Minute + rValue.Minute;

	//FIngameTime의 값은 음수를 허용하지 않을 것이므로
	//+의 결과가 음수면 오버플로의 가능성이 있음.
	if (year < 0 || month < 0 || day < 0 || hour < 0 || minute < 0)
	{
		return *this;
	}

	/*
	* 시, 분은 >= 조건 : 0 허용
	* 월, 일은 > 조건 : 0 비허용
	* 연은....그때까지 플레이하는 것이 현실적으로 불가능..
	*/

	if (minute >= MAX_MINUTE)
	{
		minute = minute % MAX_MINUTE;
		hour++;
	}

	if (hour >= MAX_HOUR)
	{
		hour = hour % MAX_HOUR;
		day++;
	}

	if (day > MAXDAY_OF_MONTH[month])
	{
		day = day % MAXDAY_OF_MONTH[month];
		month++;
	}

	if (month > MAX_MONTH)
	{
		month = month % MAX_MONTH;
		year++;
	}

	if (year > MAX_YEAR)
	{
		//Year Overflow!
		year = FMath::Clamp(year, 0, MAX_YEAR);
	}

	return FIngameDateTime(year, month, day, hour, minute);
}

FIngameDateTime& FIngameDateTime::operator+=(const FIngameDateTime& rValue)
{
	*this = *this + rValue;

	return *this;
}

FIngameDateTime FIngameDateTime::operator-(const FIngameDateTime& rValue)
{
	int32 year = this->Year - rValue.Year;
	int32 month = this->Month - rValue.Month;
	int32 day = this->Day - rValue.Day;
	int32 hour = this->Hour - rValue.Hour;
	int32 minute = this->Minute - rValue.Minute;

	if (minute < 0)
	{
		minute = minute + MAX_MINUTE;
		hour--;
	}

	if (hour < 0)
	{
		hour = hour + MAX_HOUR;
		day--;
	}

	if (day <= 0)
	{
		day = day + MAXDAY_OF_MONTH[month];
		month--;
	}

	if (month <= 0)
	{
		month = month + MAX_MONTH;
		year--;
	}

	if (year < 0)
	{
		//Year is Under 0
		year = FMath::Clamp(year, 0, MAX_YEAR);
	}

	return FIngameDateTime(year, month, day, hour, minute);
}

FIngameDateTime& FIngameDateTime::operator-=(const FIngameDateTime& rValue)
{
	*this = *this - rValue;

	return *this;
}

FString FIngameDateTime::ToString()
{
	return FString::Printf(TEXT("| Year : %d -- Month : %d -- Day : %d -- Hour : %d -- Minute : %d |"), Year, Month, Day, Hour, Minute);
}
