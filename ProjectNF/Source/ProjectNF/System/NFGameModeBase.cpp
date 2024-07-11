// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Grid/GridManager.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleActors/ElectricLink/ElectricLinkManager.h"

//private manager
TObjectPtr<UGridManager> ANFGameModeBase::GGridManager = nullptr;
TObjectPtr<UElectricLinkManager> ANFGameModeBase::GElectricLinkManager = nullptr;


ANFGameModeBase::ANFGameModeBase()
{

}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GridManager))
	{
		GridManager = NewObject<UGridManager>(this);
	}

	GGridManager = GridManager;

	if (!IsValid(ElectricLinkManager))
	{
		ElectricLinkManager = NewObject<UElectricLinkManager>(this);
	}

	GElectricLinkManager = ElectricLinkManager;


	{
		//!!���߿� ���� ���� ������ ������ ����ٸ� ���⼭ ������ ���� ��

		ElectricLinkManager->SearchAllLinks();

		GetWorldTimerManager().SetTimer(
			ElectricLinkTimer,
			ElectricLinkManager.Get(),
			&UElectricLinkManager::LinkTest,
			1.0f,
			true,
			1.0f
		);
	}

}

TObjectPtr<UGridManager> ANFGameModeBase::GetGridManager()
{
	return GGridManager;
}

TObjectPtr<UElectricLinkManager> ANFGameModeBase::GetElectricLinkManager()
{
	return GElectricLinkManager;
}
