// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmlandTile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "DebugHelper.h"
#include "GameItem/Item/ItemPickup.h"

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

	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropMesh"));
	CropMesh->SetupAttachment(RootComponent);
	CropMesh->SetCanEverAffectNavigation(false);

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

void AFarmlandTile::SetInfo(FCropData InCropData)
{
	if (!RequestCropSheetData.IsBound())
	{
		Debug::Print(DEBUG_TEXT("OnRequest is Not Bounded."));
		return;
	}

	FCropSheetData cropsheetData;
	cropsheetData = RequestCropSheetData.Execute(InCropData.CropName);

	if (cropsheetData.IsEmpty())
	{
		Debug::Print(DEBUG_TEXT("Empty Crop Sheet Data"));

		CropData = InCropData;
		RequestUpdateCropData.ExecuteIfBound(this);
		CropMesh->SetStaticMesh(nullptr);
		return;
	}

	//정상 아이템이라 판단되면 CropData를 Set함.
	CropData = InCropData;
	RequestUpdateCropData.ExecuteIfBound(this);

	int32 growthInterval = cropsheetData.MaxGrowth / 3;
	int32 growthLevel = FMath::Clamp(CropData.CurrentGrowth / growthInterval, 0, 3);
	
	switch (growthLevel)
	{
	case 0:
		CropMesh->SetStaticMesh(cropsheetData.Mesh0);
		break;
	case 1:
		CropMesh->SetStaticMesh(cropsheetData.Mesh1);
		break;
	case 2:
		CropMesh->SetStaticMesh(cropsheetData.Mesh2);
		break;
	case 3:
		CropMesh->SetStaticMesh(cropsheetData.Mesh3);
		break;
	}
}

void AFarmlandTile::Interact_Implementation(APawn* InteractCauser)
{
	//다 자란 작물을 뽑기?
	//level이 3이 되면 mesh를 삭제한다.

	//TODO : 다작 작물이면 level을 2로 떨굴 수 있게 CurrentGrowth을 떨궈야함.

	if (!RequestCropSheetData.IsBound())
	{
		Debug::Print(DEBUG_TEXT("OnRequest is Not Bound."));
		return;
	}

	FCropSheetData cropsheetData = RequestCropSheetData.Execute(CropData.CropName);

	if (cropsheetData.IsEmpty())
	{
		Debug::Print(DEBUG_TEXT("cropSheetData is empty"));
		return;
	}

	int32 growthInterval = cropsheetData.MaxGrowth / 3;
	int32 growthLevel = FMath::Clamp(CropData.CurrentGrowth / growthInterval, 0, 3);

	if (growthLevel == 3)
	{
		//초기화
		SetInfo(FCropData());

		//Item Drop
		if (!RequestSpawnItemPickup.IsBound())
		{
			Debug::Print(DEBUG_TEXT("OnRequest is Not Bound."));
			return;
		}
		
		AItemPickup* itemPickup = Cast<AItemPickup>(RequestSpawnItemPickup.Execute(TEXT("ItemPickup"), GetActorLocation() + FVector(0, 0, 50), FRotator::ZeroRotator));

		
		if (!IsValid(itemPickup))
		{
			Debug::Print(DEBUG_TEXT("Warning. ItemPickup is Invalid."));
		}

		if (IsValid(itemPickup))
		{
			FItemSlotData slotData;
			slotData.ItemName = FName(TEXT("200001"));
			slotData.Quantity = 5;
			itemPickup->SetItemPickupData(slotData);

		}
	}
	else
	{
		Debug::Print(DEBUG_TEXT("Crop Level is not 3."));
	}

}

FCropData AFarmlandTile::GetCropData() const
{
	return CropData;
}

