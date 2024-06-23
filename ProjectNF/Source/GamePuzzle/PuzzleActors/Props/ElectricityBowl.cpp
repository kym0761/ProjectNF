// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricityBowl.h"
#include "PuzzleActors/ElectricLink/ElectricLinkComponent.h"

AElectricityBowl::AElectricityBowl()
{
	ElectricLinkComponent = CreateDefaultSubobject<UElectricLinkComponent>(TEXT("ElectricLink"));
	ElectricLinkComponent->SetupAttachment(RootComponent);
}
