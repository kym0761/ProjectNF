// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GridVisualComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFARM_API UGridVisualComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UGridVisualComponent();

	UFUNCTION(BlueprintCallable)
	void DrawSingleGrid(const FVector& Location);

	UFUNCTION(BlueprintCallable)
	void DrawGridVisuals(const TArray<FVector>& ToDraws);

	UPROPERTY()
	TSet<FVector> LocationCache;

};
