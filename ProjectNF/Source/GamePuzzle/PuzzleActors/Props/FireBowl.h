// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Interfaces/PuzzleInterfaces.h"
#include "PuzzleActors/PuzzlePhysicsProp.h"
#include "FireBowl.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class GAMEPUZZLE_API AFireBowl : public APuzzlePhysicsProp, public ICombustible
{
	GENERATED_BODY()
	
public:
	AFireBowl();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire|Effect")
	TObjectPtr<UBoxComponent> FireOverlap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire|Effect")
	TObjectPtr<UNiagaraComponent> FireEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire|Variable")
	bool bFireOn;

	FTimerHandle CombustTimer;

public:

	virtual void Combust() override;

	virtual void Extinguish() override;

	virtual void TurnOn() override;
	virtual void TurnOff() override;

	UFUNCTION()
	void OverlapCombust();

};
