// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "Managers/ObjectManager.h"
#include "System/NFGameInstance.h"
#include "DebugHelper.h"
void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	auto testWidget = UNFGameInstance::GetObjectManager()
		->CreateWidgetFromName(TEXT("CreateTest"), GetOwningPlayer());

	testWidget->AddToViewport();

	Debug::Print(DEBUG_TEXT("HUD Construct"));
}
