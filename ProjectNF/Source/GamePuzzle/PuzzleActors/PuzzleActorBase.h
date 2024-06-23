// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleActorBase.generated.h"

UCLASS(abstract)
class GAMEPUZZLE_API APuzzleActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActorBase();

protected:

	//이 actor가 트리거 동작이 되고 있는가?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	bool bTriggerActive;

	//World에서 트리거하기를 원하는 액터를 선택해서 넣어야함.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TObjectPtr<APuzzleActorBase>> TriggerTargets;

	//누가 이 액터를 Trigger하는지는 ToTrigger에 있는 액터가 BeginPlay()에서 추가됨.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<APuzzleActorBase>> WhoTriggerThis;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//WhoTriggerThis를 Init함.
	void InitWhoTriggerThis();

public:

	bool GetTriggerActive() const;

};
