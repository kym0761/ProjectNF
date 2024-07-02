// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmlandTile.generated.h"


USTRUCT(BlueprintType)
struct GAMEFARM_API FCropData
{
	GENERATED_BODY()

public:

	//FarmTile에 들어갈 Crop 정보 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FName CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 MaxGrowth;

};

class UStaticMeshComponent;
class UBoxComponent;
/*
* Grid를 점유하고 작물을 키울 땅 타일
* 작물의 정보와 성장 정도에 따라 땅 Mesh 위에 작물 Mesh가 나타날 것
*/
UCLASS()
class GAMEFARM_API AFarmlandTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmlandTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> TileMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
