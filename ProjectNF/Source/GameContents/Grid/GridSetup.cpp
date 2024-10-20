// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSetup.h"
#include "GridVisualComponent.h"

// Sets default values
AGridSetup::AGridSetup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	GridVisual = CreateDefaultSubobject<UGridVisualComponent>(TEXT("GridVisual"));
	GridVisual->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AGridSetup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGridSetup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FGrid AGridSetup::WorldToGrid(const FVector& WorldLocation) const
{
	FGrid grid;

	//grid.X = FMath::CeilToInt32(WorldLocation.X / CellSize);
	//grid.Y = FMath::CeilToInt32(WorldLocation.Y / CellSize);

	//GridSubsystem으로 기능을 옮김.
	//추후 삭제 예정

	return grid;
}

FVector AGridSetup::GridToWorld(const FGrid& Grid) const
{
	FVector worldLocation = FVector::ZeroVector;
	//worldLocation.X += Grid.X * CellSize - CellSize / 2;
	//worldLocation.Y += Grid.Y * CellSize - CellSize / 2;

	//GridSubsystem으로 기능을 옮김.

	return worldLocation;
}

