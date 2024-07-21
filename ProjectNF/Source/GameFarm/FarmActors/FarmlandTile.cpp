// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmlandTile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "System/NFGameInstance.h"
#include "DebugHelper.h"
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
	CropData = InCropData;

	//CropData.CropName;
	//CropData.bWatered;
	//CropData.CurrentGrowth;

	auto gameinstance = UNFGameInstance::GetNFGameInstance();

	if (!IsValid(gameinstance))
	{
		Debug::Print(DEBUG_TEXT("gameinstance invalid."));
		return;
	}

	FCropSheetData cropsheetData;
	gameinstance->GetCropDataFromSheet(InCropData.CropName, cropsheetData);

	int32 growthInterval = cropsheetData.MaxGrowth / 3;
	int32 growthLevel = CropData.CurrentGrowth / growthInterval;
	
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
}

