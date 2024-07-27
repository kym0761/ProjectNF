// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActors/PuzzleActorBase.h"
#include "Defines/Interfaces/PuzzleInterfaces.h"
#include "PuzzleButton.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class GAMEPUZZLE_API APuzzleButton : public APuzzleActorBase, public ITriggerable
{
	GENERATED_BODY()
	
public:
	APuzzleButton();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Variable")
	FVector ButtonUpPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Variable")
	FVector ButtonDownPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Variable")
	bool bButtonActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|IntervalSettings")
	float TriggerInterval;

	float TriggerTimer = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
	void OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void ButtonUp(); // virtual for ResetButton. See ResetButtonTrigger.h
	void ButtonDown();

	virtual void Trigger() override;

};
