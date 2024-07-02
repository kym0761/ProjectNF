// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmlandTile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFarmlandTile::AFarmlandTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetCanEverAffectNavigation(false);

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(RootComponent);
	TileMesh->SetCanEverAffectNavigation(false);

}

// Called when the game starts or when spawned
void AFarmlandTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmlandTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

