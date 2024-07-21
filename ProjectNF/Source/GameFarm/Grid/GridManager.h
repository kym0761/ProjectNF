// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid.h"
#include "interfaces.h"
#include "GridManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFARM_API UGridManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UGridManager();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
		float CellSize = 200.0f;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;

	virtual void ManagerInit() override;
};
