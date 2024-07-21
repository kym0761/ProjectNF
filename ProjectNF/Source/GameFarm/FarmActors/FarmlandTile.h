// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Defines/Data.h"
#include "Defines/Interfaces.h"
#include "FarmlandTile.generated.h"



class UStaticMeshComponent;
class UBoxComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> TileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> CropMesh;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crop")
	FCropData CropData;

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
