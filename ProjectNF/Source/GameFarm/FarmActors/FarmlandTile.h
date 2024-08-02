// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Defines/Data.h"
#include "Defines/Interfaces/InteractiveInterfaces.h"
#include "FarmlandTile.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AItemPickup;

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FCropSheetData, FRequestCropSheetData, const FName&, CropID);
DECLARE_DYNAMIC_DELEGATE_RetVal_ThreeParams(AActor*, FRequestSpawnItemPickup, FString, ToSpawnClassName, const FVector&, Location, const FRotator&, Rotator);

DECLARE_DYNAMIC_DELEGATE_OneParam(FRequestUpdateCropData, AFarmlandTile*, TargetFarmlandTile);
DECLARE_DYNAMIC_DELEGATE_OneParam(FRequestRemoveCropData, AFarmlandTile*, TargetFarmlandTile);
/*
* Grid를 점유하고 작물을 키울 땅 타일
* 작물의 정보와 성장 정도에 따라 땅 Mesh 위에 작물 Mesh가 나타날 것
*/
UCLASS()
class GAMEFARM_API AFarmlandTile : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmlandTile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> TileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> CropMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crop")
	FCropData CropData;

public:

	//CropSheetData를 얻는 것을 요청.
	UPROPERTY()
	FRequestCropSheetData RequestCropSheetData;

	//ItemPickup을 Spawn하는 것을 요청.
	UPROPERTY()
	FRequestSpawnItemPickup RequestSpawnItemPickup;

	//FarmlandTile을 추가할 때 요청.
	UPROPERTY()
	FRequestUpdateCropData RequestUpdateCropData;

	//FarmlandTile을 제거할 때 요청.
	UPROPERTY()
	FRequestRemoveCropData RequestRemoveCropData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) //임시로 성장 기능을 캐릭터 블루프린트에서 진행함. 추후 기능 완성시 삭제해도 됨.
	void SetInfo(FCropData InCropData);

	virtual void Interact_Implementation(APawn* InteractCauser);

	FCropData GetCropData() const;
};
