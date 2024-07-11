// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Grid.h"
#include "FarmlandTile.generated.h"


//FarmlandTile�� �� Crop ���� 
USTRUCT(BlueprintType)
struct GAMEFARM_API FCropData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FName CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 MaxGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	bool bWatered;

};

//SaveGame�� ����� ���̺�� ����ü
//Grid ��ġ���� �����Ͽ� load�ϰ� farm�ʿ��� Grid��ġ�� �°� ��ġ�� �뵵
USTRUCT(BlueprintType)
struct GAMEFARM_API FFarmlandTimeSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FName CropName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	int32 MaxGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	bool bWatered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crop")
	FGrid Grid;

};

class UStaticMeshComponent;
class UBoxComponent;
/*
* Grid�� �����ϰ� �۹��� Ű�� �� Ÿ��
* �۹��� ������ ���� ������ ���� �� Mesh ���� �۹� Mesh�� ��Ÿ�� ��
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
