// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"

#include "DebugHelper.h"
//#include "Components/InventoryComponent.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemVisual = CreateDefaultSubobject<UBillboardComponent>(TEXT("ItemVisual"));
	SetRootComponent(ItemVisual);
	ItemVisual->SetHiddenInGame(false);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->InitSphereRadius(64.0f);

	//ItemVisual->SetEnableGravity(true);
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();

	{
		//아이템이 맵에 배치되어 있을때 ItemData가 정해져있다면, 시작할 때 PickupItemData를 사용해 아이템 정보를 세팅해준다.
		SetItemPickupData(PickupItemData);
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


	bool bAdded= RequestAddItem.Execute(InteractCauser, PickupItemData);

	if (bAdded)
	{
		FMyDebug::Print(DEBUG_TEXT("Item will be Added to Inventory."));
		RequestDespawn.ExecuteIfBound(this);
	}

}

void AItemPickup::SetItemPickupData(FItemSlotData SlotData)
{
	PickupItemData = SlotData;

	FMyDebug::Print(DEBUG_VATEXT(TEXT("Set Item Pickup Data : %s, %d"), *PickupItemData.ItemName.ToString(), PickupItemData.Quantity));

	if (!RequestItemData.IsBound())
	{
		FMyDebug::Print(DEBUG_TEXT("Request Item Data Not Bound."));
		return;
	}

	auto itemData = RequestItemData.Execute(PickupItemData.ItemName);
	
	ItemVisual->SetSprite(itemData.Thumbnail);
}

FItemSlotData AItemPickup::GetPickupItemData() const
{
	return PickupItemData;
}

