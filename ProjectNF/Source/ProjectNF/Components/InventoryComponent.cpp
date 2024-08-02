// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "System/NFGameInstance.h"
#include "Managers/InventoryManager.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	//InventorySize = 100;

	//InitializeInventory();
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(DEBUG_TEXT("Inventory Component BeginPlay()"));

}

void UInventoryComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	////InventorySize의 값이 변경됐을 때 인벤토리의 크기를 다시 재조정한다.
	//FProperty* prop = PropertyChangedEvent.Property;
	//if (prop->GetName() == TEXT("InventorySize"))
	//{
	//	//InitializeInventory();
	//}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InitInventoryComponent()
{
	Debug::Print(DEBUG_TEXT("Inventory Component Init()"));

	auto inventoryManager = UNFGameInstance::GetInventoryManager();

	if (IsValid(inventoryManager))
	{
		InventoryObjectRef = inventoryManager->TryGetInventory(InventoryID);
	}
	else
	{
		Debug::Print(DEBUG_TEXT("Inventory Manager is Invalid."));
	}
}

UInventoryObject* UInventoryComponent::GetInventoryObjectRef()
{
	return InventoryObjectRef;
}

