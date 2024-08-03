// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "Defines/StatAttribute.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	HP = CreateDefaultSubobject<UStatAttribute>(TEXT("HP"));
	Mana = CreateDefaultSubobject<UStatAttribute>(TEXT("Mana"));
	Stamina = CreateDefaultSubobject<UStatAttribute>(TEXT("Stamina"));
	Attack = CreateDefaultSubobject<UStatAttribute>(TEXT("Attack"));
	Defence = CreateDefaultSubobject<UStatAttribute>(TEXT("Defence"));

}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

