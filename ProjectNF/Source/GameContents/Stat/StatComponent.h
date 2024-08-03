// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

class UStatAttribute;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECONTENTS_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Stat", Meta = (AllowPrivateAccess))
	UStatAttribute* HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess))
	UStatAttribute* Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess))
	UStatAttribute* Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess))
	UStatAttribute* Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (AllowPrivateAccess))
	UStatAttribute* Defence;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
