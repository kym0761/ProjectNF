// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
//#include "Managers/ObjectManager.h"
#include "DebugHelper.h"
#include "Subsystems/ObjectSubsystem.h"
void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	//BP_로 만든 UMG도 Spawn가능
	{
		auto objectSubsystem = GEngine->GetEngineSubsystem<UObjectSubsystem>();

		auto testWidget = objectSubsystem->CreateWidgetBlueprint(TEXT("CreateTest"), GetOwningPlayer());
		testWidget->AddToViewport();
		FMyDebug::Print(DEBUG_TEXT("HUD Construct"));
	}
	
}
