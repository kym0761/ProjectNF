// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleButton.h"
#include "ResetPuzzleButton.generated.h"

/**
 * 
 */
UCLASS()
class GAMECONTENTS_API AResetPuzzleButton : public APuzzleButton
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

#if WITH_EDITOR
protected:

	//ResetButton은 TriggerMap을 건드리면 안됨.
	//Actor:: 의 함수로 기능 자체를 초기화함.
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif // WITH_EDITOR

};
