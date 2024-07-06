// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.generated.h"

/**
 *  구조체 _API 명시 안하고 사용하면 메인 모듈에서 사용시 버그 발생함.
 */
USTRUCT(BlueprintType, Blueprintable)
struct GAMEFARM_API FGrid
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Y;

	FGrid();
	FGrid(int32 _X, int32 _Y);
	FString ToString() const;
	bool operator==(const FGrid& Other) const;
	bool operator!= (const FGrid& Other) const;
	FGrid operator+(const FGrid& b) const;
	FGrid operator-(const FGrid& b) const;
	FGrid& operator=(const FGrid& b);
	FGrid& operator+=(const FGrid& b);
	FGrid& operator-=(const FGrid& b);
	int32 Size() const;

	bool IsInvalidGrid() const;
};

//외부 모듈에서 이 Hash가 적용되려면 GAMEFARM_API가 함수 앞에 붙어야하는 것으로 보임.
//hash : TSet, TMap..
GAMEFARM_API uint32 GetTypeHash(const FGrid& Grid);