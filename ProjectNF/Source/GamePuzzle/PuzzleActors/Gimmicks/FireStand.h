// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/PuzzleInterfaces.h"
#include "PuzzleActors/PuzzleActorBase.h"
#include "FireStand.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class UNiagaraComponent;
//class UNiagaraSystem;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class GAMEPUZZLE_API AFireStand : public APuzzleActorBase, public ITriggerable, public IBeTriggerable, public IResetable, public ICombustible
{
	GENERATED_BODY()
	
public:

	AFireStand();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Stand;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	//TObjectPtr<UWidgetComponent> Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraComponent> FireEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> FireOverlap;

	FTimerHandle CombustTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	virtual void Trigger_Implementation();
	
	virtual void BeTriggered_Implementation();

	virtual void Reset_Implementation();

	virtual void Combust_Implementation();

	virtual void Extinguish_Implementation();

	UFUNCTION()
	void OverlapCombust();

	virtual void TurnOn() override;
	virtual void TurnOff() override;

};
