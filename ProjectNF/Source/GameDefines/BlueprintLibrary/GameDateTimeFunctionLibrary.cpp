// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDateTimeFunctionLibrary.h"

FGameDateTime UGameDateTimeFunctionLibrary::Plus_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 + InValue2;
}

FGameDateTime UGameDateTimeFunctionLibrary::Minus_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 - InValue2;
}

bool UGameDateTimeFunctionLibrary::Less_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 < InValue2;
}

bool UGameDateTimeFunctionLibrary::LessEqual_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 <= InValue2;
}

bool UGameDateTimeFunctionLibrary::Greater_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 > InValue2;
}

bool UGameDateTimeFunctionLibrary::GreaterEqual_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2)
{
    return InValue1 >= InValue2;
}

FString UGameDateTimeFunctionLibrary::Conv_GameDateTimeToString(FGameDateTime InGameDateTime)
{
    return InGameDateTime.ToString();
}

int32 UGameDateTimeFunctionLibrary::GetYear(FGameDateTime InGameDateTime)
{
    return InGameDateTime.Year;
}

int32 UGameDateTimeFunctionLibrary::GetMonth(FGameDateTime InGameDateTime)
{
    return InGameDateTime.Month;
}

int32 UGameDateTimeFunctionLibrary::GetDay(FGameDateTime InGameDateTime)
{
    return InGameDateTime.Day;
}

int32 UGameDateTimeFunctionLibrary::GetHour(FGameDateTime InGameDateTime)
{
    return InGameDateTime.Hour;
}

int32 UGameDateTimeFunctionLibrary::GetMinute(FGameDateTime InGameDateTime)
{
    return InGameDateTime.Minute;
}

FGameDateTime UGameDateTimeFunctionLibrary::GetMorning()
{
    return FGameDateTime::MORNING;
}

FGameDateTime UGameDateTimeFunctionLibrary::GetNoon()
{
    return FGameDateTime::NOON;
}

FGameDateTime UGameDateTimeFunctionLibrary::GetEvening()
{
    return FGameDateTime::EVENING;
}
