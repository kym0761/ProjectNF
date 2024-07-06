// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.h" // TMap�� Ű�� ���� �̻�, �� �� ����.
#include "GridSetup.generated.h"

class UGridVisualComponent;

UCLASS()
class GAMEFARM_API AGridSetup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSetup();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")//, Meta = (AllowPrivateAccess = true))
	float CellSize = 100.0f;


protected:

	//Grid ǥ���� InstancedMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UGridVisualComponent> GridVisual;

	////Grid�� � Actor�� �����ϰ� �ִ��� üũ�ϴ� Map
	////�� ��� ������ Grid�� ������ �ʰ� �ʿ��� ������ �����Ѵ�.
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
