// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Defines/Data.h"// TMap의 키로 쓰는 이상, 뺄 수 없음.
#include "GridSetup.generated.h"

class UGridVisualComponent;

UCLASS()
class GAMECONTENTS_API AGridSetup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSetup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")//, Meta = (AllowPrivateAccess = true))
	float CellSize = 200.0f;


protected:

	//Grid 표시할 InstancedMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UGridVisualComponent> GridVisual;

	////Grid에 어떤 Actor가 점유하고 있는지 체크하는 Map
	////맵 모든 지역을 Grid로 만들지 않고 필요한 정보만 보관한다.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	//TMap<FGrid, TObjectPtr< AActor>> Occupy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;
};
