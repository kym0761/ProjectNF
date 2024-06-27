// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleButton.h"
#include "ResetPuzzleButton.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPUZZLE_API AResetPuzzleButton : public APuzzleButton
{
	GENERATED_BODY()

public :

	AResetPuzzleButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ButtonUp() override;

	virtual void Trigger() override;

};
