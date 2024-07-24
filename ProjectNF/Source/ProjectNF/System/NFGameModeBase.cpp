// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NFGameInstance.h"

ANFGameModeBase::ANFGameModeBase()
{

}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	auto gameinstance= Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameinstance->InitManagers();

	gameinstance->Init();
}