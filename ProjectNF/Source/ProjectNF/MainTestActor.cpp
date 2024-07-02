// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTestActor.h"
#include "Inventory/InventoryComponent.h"
#include "GameFarm/FarmActors/FarmlandTile.h"
#include "UI/InventoryWidget.h"
#include "Interfaces/PuzzleInterfaces.h"

// Sets default values
AMainTestActor::AMainTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

