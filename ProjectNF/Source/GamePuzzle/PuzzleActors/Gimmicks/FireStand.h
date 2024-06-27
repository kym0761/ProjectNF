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
	TObjectPtr<UBoxComponent> FireOverlap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire|Effect")
	TObjectPtr<UNiagaraComponent> FireEffect;

	//화로대는 bPuzzleActive보다 bFireOn의 우선순위가 높음.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire|Variable")
	bool bFireOn;

protected:

	FTimerHandle CombustTimer;

	const float FireInterval = 0.33f;
	float fireCount = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	virtual void Trigger() override;
	
	virtual void BeTriggered(TObjectPtr<class APuzzleActorBase> TriggerActor, bool TriggerValue) override;

	virtual void Reset() override;

	virtual void Combust() override;

	virtual void Extinguish() override;

	UFUNCTION()
	void OverlapCombust();

	virtual void TurnOn() override;
	virtual void TurnOff() override;

};
