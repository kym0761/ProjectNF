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

	////임시로 gamemode에서 gameinstance를 초기화함.
	////원래대로면 타이틀에서 Level 이동하기 전에 Gameinstance를 초기화해야한다.

	//auto gameinstance = Cast<UNFGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//if (!IsValid(gameinstance))
	//{
	//	Debug::Print(DEBUG_TEXT("gameinstance is invalid."));
	//	return;
	//}

	//gameinstance->InitNFGameInstance();

}

void ANFGameModeBase::StartPlay()
{
	Super::StartPlay();
}
