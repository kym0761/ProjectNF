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

	////Grid에 어떤 Actor가 점유하고 있는지 체크하는 Map
	////맵 모든 지역을 Grid로 만들지 않고 필요한 정보만 보관한다.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid", Meta = (AllowPrivateAccess = true))
	//TMap<FGrid, TObjectPtr<AActor>> Occupy;

	////유저가 설치한 건물류 액터?
	////key : int , value : Grid,Grid,Grid,Grid..
	////key 다른 값으로 교체될 수도 있음
	//TMultiMap<int32, FGrid> UserStaticActors;

public:

	UFUNCTION(BlueprintCallable)
	FGrid WorldToGrid(const FVector& WorldLocation) const;
	UFUNCTION(BlueprintCallable)
	FVector GridToWorld(const FGrid& Grid) const;

	bool IsSomethingExistOnGrid(const FGrid& Grid) const;
};
