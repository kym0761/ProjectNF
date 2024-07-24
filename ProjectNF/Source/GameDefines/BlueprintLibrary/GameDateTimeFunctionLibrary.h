// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Defines/Data.h"
#include "GameDateTimeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEFINES_API UGameDateTimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime + GameDateTime",
		CompactNodeTitle = "+", KeyWords = "+ Plus", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Convert")
	static FGameDateTime Plus_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime - GameDateTime",
		CompactNodeTitle = "-", KeyWords = "- Minus", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Convert")
	static FGameDateTime Minus_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime < GameDateTime",
		CompactNodeTitle = "<", KeyWords = "< Less", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Compare")
	static bool Less_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime <= GameDateTime",
		CompactNodeTitle = "<=", KeyWords = "<= LessEqual", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Compare")
	static bool LessEqual_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime > GameDateTime",
		CompactNodeTitle = ">", KeyWords = "> Greater", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Compare")
	static bool Greater_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameDateTime >= GameDateTime",
		CompactNodeTitle = ">=", KeyWords = ">= GreaterEqual", CommutativeAssosiativeBinaryOperator = "true"),
		Category = "GameDateTime|Compare")
	static bool GreaterEqual_GameDateTime_GameDateTime(FGameDateTime InValue1, FGameDateTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (GameDateTime)",
		CompactNodeTitle = "->", BlueprintAutocast),
		Category = "GameDateTime|Convert")
	static FString Conv_GameDateTimeToString(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static int32 GetYear(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static int32 GetMonth(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static int32 GetDay(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static int32 GetHour(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static int32 GetMinute(FGameDateTime InGameDateTime);

	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static FGameDateTime GetMorning();
	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static FGameDateTime GetNoon();
	UFUNCTION(BlueprintPure, Category = "GameDateTime|Get")
	static FGameDateTime GetEvening();

};
