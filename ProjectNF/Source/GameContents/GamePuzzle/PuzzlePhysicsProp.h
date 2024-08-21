// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePhysicsProp.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GAMECONTENTS_API APuzzlePhysicsProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzlePhysicsProp();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Mesh;

	//혹시 나중에 가져오는게 불가능한 위치에 놓였을 때, 초기화하면 초기 위치로 불러들이는 용도?
	//즉, 아직 사용 안하고 있는 값이다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector DefaultPosition;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
