// Fill out your copyright notice in the Description page of Project Settings.


#include "GridVisualComponent.h"
#include "Grid.h"

UGridVisualComponent::UGridVisualComponent()
{
	SetCollisionProfileName(TEXT("NoCollision"));

	SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	////사용가능한 Material의 Custom Data Value의 최대 갯수
	//NumCustomDataFloats = 8;
}

void UGridVisualComponent::DrawSingleGrid(const FVector& Location)
{
	ClearInstances();

	FTransform transform;
	transform.SetLocation(Location);
	AddInstance(transform, true);

}
