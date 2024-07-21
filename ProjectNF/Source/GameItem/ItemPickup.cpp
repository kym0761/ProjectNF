// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(64.0f);
	Sphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemPickup::Interact_Implementation(APawn* InteractCauser)
{

	//pawn�� �κ��丮�� ����

	//�κ��丮�� ������, �κ��丮 �ȿ� PickupItemData ������ ����.

}

