// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePuzzle/PuzzlePhysicsProp.h"
#include "ElectricityBowl.generated.h"


class UElectricLinkComponent;
/**
 * 
 */
UCLASS()
class GAMECONTENTS_API AElectricityBowl : public APuzzlePhysicsProp
{
	GENERATED_BODY()
	
public:

	AElectricityBowl();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UElectricLinkComponent> ElectricLinkComponent;

};
