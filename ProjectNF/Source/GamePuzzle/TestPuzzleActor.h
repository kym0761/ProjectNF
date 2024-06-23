// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPuzzleActor.generated.h"

UCLASS()
class GAMEPUZZLE_API ATestPuzzleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestPuzzleActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Trigger")
	class UTriggerObjectBase* TriggerObject;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
