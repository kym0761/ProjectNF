// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ElectricLinkComponent.generated.h"

class UNiagaraSystem;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEPUZZLE_API UElectricLinkComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UElectricLinkComponent();

	//이 값이 true면, 무조건 Activate한다
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	bool bRootLink;

	//인접한 LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	TSet<TObjectPtr<UElectricLinkComponent>> AdjacentLinkComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	TObjectPtr<UNiagaraSystem> ElectricNiagaraBP;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	bool bLinkActivated;

	FTimerHandle LinkJobTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void LinkJob();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ElectricLinkActivate();
	void ElectricLinkDeactivate();
};
