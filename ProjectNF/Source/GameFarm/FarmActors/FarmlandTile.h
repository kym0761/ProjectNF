// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Defines/Data.h"
#include "Defines/Interfaces.h"
#include "FarmlandTile.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class AItemPickup;

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FCropSheetData, FOnRequestCropSheetData, const FName&, CropID);
DECLARE_DYNAMIC_DELEGATE_RetVal_FourParams(AActor*, FOnRequestSpawnItemPickup, UObject*, WorldContext, TSubclassOf<AActor>, AItemPickup_BP, const FVector&, Location, const FRotator&, Rotator);

/*
* Grid�� �����ϰ� �۹��� Ű�� �� Ÿ��
* �۹��� ������ ���� ������ ���� �� Mesh ���� �۹� Mesh�� ��Ÿ�� ��
*/
UCLASS()
class GAMEFARM_API AFarmlandTile : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmlandTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> TileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> CropMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crop")
	FCropData CropData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="Crop", Meta=(AllowPrivateAccess = true))
	TSubclassOf<AItemPickup> ItemPickup_BP;

public:

	//CropSheetData�� ��� ���� ��û.
	UPROPERTY()
	FOnRequestCropSheetData OnRequestCropSheetData;

	//ItemPickup�� Spawn�ϴ� ���� ��û.
	UPROPERTY()
	FOnRequestSpawnItemPickup OnRequestSpawnItemPickup;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetInfo(FCropData InCropData);

	virtual void Interact_Implementation(APawn* InteractCauser);
};
