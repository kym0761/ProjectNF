// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActors/PuzzleActorBase.h"
#include "Defines/Interfaces/PuzzleInterfaces.h"
#include "ElectricPuzzleDevice.generated.h"

class UElectricLinkComponent;

/**
 * 
 */
UCLASS()
class GAMEPUZZLE_API AElectricPuzzleDevice : public APuzzleActorBase, public ITriggerable
{
	GENERATED_BODY()

public:
	AElectricPuzzleDevice();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UElectricLinkComponent> ElectricLinkComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Puzzle")
	bool bPuzzleActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	bool bIsRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetPuzzleActiveByLink(bool InVal);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Inherited via ITriggerable
	void Trigger() override;

};
