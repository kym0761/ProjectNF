// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
//#include "System/NFGameInstance.h"
#include "GameItem/Inventory/InventoryObject.h"
#include "DebugHelper.h"

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

	//FMyDebug::Print(DEBUG_TEXT("Inventory Component BeginPlay()"));

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InitInventoryComponent()
{
	FMyDebug::Print(DEBUG_TEXT("Inventory Component Init()"));

	if (RequestTryGetInventory.IsBound())
	{
		InventoryObjectRef = //UNFGameInstance::TryGetInventory(InventoryID);
			RequestTryGetInventory.Execute(InventoryID);
	}

	if (IsValid(InventoryObjectRef))
	{
		FMyDebug::Print(DEBUG_TEXT("InventoryObjectRef is OK."));
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("InventoryObjectRef is Invalid."));
	}
}

UInventoryObject* UInventoryComponent::GetInventoryObjectRef()
{
	return InventoryObjectRef;
}

bool UInventoryComponent::AddItemToInventory(FItemSlotData SlotData)
{
	int32 leftover = InventoryObjectRef->AddItemToInventory(SlotData);

	return (leftover == 0) ? true : false;
}

