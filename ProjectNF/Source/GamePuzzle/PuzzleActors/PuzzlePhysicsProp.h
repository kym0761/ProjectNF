// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePhysicsProp.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GAMEPUZZLE_API APuzzlePhysicsProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzlePhysicsProp();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Mesh;

	//���� �̻��� �������� ���� ������ �Ұ����ϸ�, �ǵ��ƿ� ��ġ?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector DefaultPosition;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
