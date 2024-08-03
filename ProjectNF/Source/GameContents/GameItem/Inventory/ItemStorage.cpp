// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStorage.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "InventoryComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AItemStorage::AItemStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageMesh"));
	SetRootComponent(StorageMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StorageMesh);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

	//InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AItemStorage::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItemStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

