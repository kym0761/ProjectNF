// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTNF_API UNFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNFGameInstance();

protected:

	//player ¿Ã∏ß
	UPROPERTY()
	FString PlayerName;
	
	//?
	UPROPERTY()
	int32 PlayerNumber;

#pragma region SaveGameFunction

public:

	UFUNCTION()
	void Save();

	UFUNCTION()
	void Load();
#pragma endregion


};
