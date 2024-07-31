// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmlandTile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "DebugHelper.h"
#include "Item/ItemPickup.h"

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
	FCropSheetData cropsheetData;

	if (!OnRequestCropSheetData.IsBound())
	{
		Debug::Print(DEBUG_TEXT("OnRequest is Not Bounded."));
		return;
	}
	cropsheetData = OnRequestCropSheetData.Execute(InCropData.CropName);

	if (cropsheetData.IsEmpty())
	{
		Debug::Print(DEBUG_TEXT("Empty Crop Sheet Data"));
		return;
	}

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

	//정상 아이템이라 판단되면 CropData를 Set함.
	CropData = InCropData;

}

void AFarmlandTile::Interact_Implementation(APawn* InteractCauser)
{
	//다 자란 작물을 뽑기?
	//level이 3이 되면 mesh를 삭제한다.

	//TODO : 다작 작물이면 level을 2로 떨굴 수 있게 growthLevel을 떨궈야함.

	if (!OnRequestCropSheetData.IsBound())
	{
		Debug::Print(DEBUG_TEXT("OnRequest is Not Bound."));
		return;
	}

	FCropSheetData cropsheetData = OnRequestCropSheetData.Execute(CropData.CropName);

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
		CropMesh->SetStaticMesh(nullptr);
		CropData = FCropData();

		//Item Drop
		if (!OnRequestSpawnItemPickup.IsBound())
		{
			Debug::Print(DEBUG_TEXT("OnRequest is Not Bound."));
			return;
		}
		
		OnRequestSpawnItemPickup.Execute(TEXT("ItemPickup"), GetActorLocation() + FVector(0, 0, 50), FRotator::ZeroRotator);

	}
	else
	{
		Debug::Print(DEBUG_TEXT("Crop Level is not 3."));
	}

}

