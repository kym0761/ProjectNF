// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NFGameInstance.h"
#include "DebugHelper.h"
ANFGameModeBase::ANFGameModeBase()
{

}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ANFGameModeBase::StartPlay()
{
	Super::StartPlay();

	auto gameinstance = Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!IsValid(gameinstance))
	{
		Debug::Print(DEBUG_TEXT("gameinstance is invalid."));
		return;
	}

	gameinstance->InitNFGameInstance();
}
