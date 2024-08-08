// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"

#include "Components/InventoryComponent.h"

#include "DebugHelper.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectPoolManager.h"
#include "Managers/DataManager.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemVisual = CreateDefaultSubobject<UBillboardComponent>(TEXT("ItemVisual"));
	SetRootComponent(ItemVisual);
	ItemVisual->SetHiddenInGame(false);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(64.0f);
	Sphere->SetupAttachment(RootComponent);

	//ItemVisual->SetEnableGravity(true);
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();

	{
		auto itemData = UNFGameInstance::GetDataManager()->GetItemData(PickupItemData.ItemName);
		ItemVisual->SetSprite(itemData.Thumbnail);
	}
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemPickup::Interact_Implementation(APawn* InteractCauser)
{
	FMyDebug::Print(DEBUG_TEXT("ItemPickup Interact Ok."));
	//pawn의 인벤토리에 접근

	//인벤토리가 있으면, 인벤토리 안에 PickupItemData 정보를 넣음.


	auto inventoryComponent = InteractCauser->FindComponentByClass<UInventoryComponent>();
	if (!IsValid(inventoryComponent))
	{
		FMyDebug::Print(DEBUG_TEXT("No Inventory comp."));
	}

	bool bAdded = inventoryComponent->AddItemToInventory(PickupItemData);

	if (bAdded)
	{
		FMyDebug::Print(DEBUG_TEXT("Item Added to Inventory."));
		UNFGameInstance::GetObjectPoolManager()->DespawnToPool(this);
	}

}

void AItemPickup::SetItemPickupData(FItemSlotData SlotData)
{
	PickupItemData = SlotData;
	FMyDebug::Print(DEBUG_VATEXT(TEXT("Set Item Pickup Data : %s, %d"), *PickupItemData.ItemName.ToString(), PickupItemData.Quantity));

	auto itemData = UNFGameInstance::GetDataManager()->GetItemData(PickupItemData.ItemName);

	ItemVisual->SetSprite(itemData.Thumbnail);
}

