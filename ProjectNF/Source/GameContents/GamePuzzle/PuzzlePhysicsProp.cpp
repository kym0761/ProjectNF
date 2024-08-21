// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePhysicsProp.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APuzzlePhysicsProp::APuzzlePhysicsProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetSimulatePhysics(true);
	Box->BodyInstance.bLockXRotation = true;
	Box->BodyInstance.bLockYRotation = true;
	//Box->BodyInstance.bLockZRotation = true;

	//Box->SetCollisionProfileName(TEXT("InteractiveCollision"));
	//Box->bDynamicObstacle = true;
	Box->SetCanEverAffectNavigation(false);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCanEverAffectNavigation(false);

}

// Called when the game starts or when spawned
void APuzzlePhysicsProp::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultPosition = GetActorLocation();
}

// Called every frame
void APuzzlePhysicsProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

