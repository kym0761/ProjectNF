// Fill out your copyright notice in the Description page of Project Settings.


#include "NFGameModeBase.h"
#include "Grid/GridManager.h"
#include "Kismet/GameplayStatics.h"

TObjectPtr<UGridManager> ANFGameModeBase::GGridManager = nullptr;

ANFGameModeBase::ANFGameModeBase()
{
	GridManager = CreateDefaultSubobject<UGridManager>(TEXT("GridManager"));
}

void ANFGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GridManager))
	{
		GridManager = NewObject<UGridManager>(this);
	}

	GGridManager = GridManager;

}

TObjectPtr<UGridManager> ANFGameModeBase::GetGridManager()
{
	return GGridManager;
}
