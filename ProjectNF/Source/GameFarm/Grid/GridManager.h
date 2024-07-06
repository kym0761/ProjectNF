// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Grid.h"
#include "GridManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFARM_API UGridManager : public UObject
{
	GENERATED_BODY()

public:

	UGridManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")//, Meta = (AllowPrivateAccess = true))
		float CellSize = 100.0f;

	////Grid�� � Actor�� �����ϰ� �ִ��� üũ�ϴ� Map
	////�� ��� ������ Grid�� ������ �ʰ� �ʿ��� ������ �����Ѵ�.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	//TMap<FGrid, TObjectPtr<AActor>> Occupy;

	////������ ��ġ�� �ǹ��� ����?
	////key : int , value : Grid,Grid,Grid,Grid..
	////key �ٸ� ������ ��ü�� ���� ����
	//TMultiMap<int32, FGrid> UserStaticActors;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;
};
