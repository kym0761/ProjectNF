// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Grid.h"
#include "GameDateTime.h"
#include "MainTestActor.generated.h"

//모듈 적용이 제대로 되는지 확인하기 위한 Actor
//필요없으면 삭제할 것.

UCLASS()
class PROJECTNF_API AMainTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainTestActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
