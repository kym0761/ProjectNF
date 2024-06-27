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

	//World���� Ʈ�����ϱ⸦ ���ϴ� ���͸� �����ؼ� �־����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TObjectPtr<APuzzleActorBase>> TriggerTargets;

private:

	//TriggerTargets���� �� ���͸� Ʈ���Ÿ� ������� Ȯ���ϱ� ���� TMap
	//key : ActorName, Value : bool
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> TriggerMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//WhoTriggerThis�� Init��.
	void InitTriggerMap();

public:

	void SendTriggerParams(TObjectPtr<APuzzleActorBase> TriggerActor, bool Val);

	bool CheckTriggersHaveActivated() const;

};
