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

	//World에서 트리거하기를 원하는 액터를 선택해서 넣어야함.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TObjectPtr<APuzzleActorBase>> TriggerTargets;

private:

	//TriggerTargets들이 이 액터를 트리거를 해줬는지 확인하기 위한 TMap
	//key : ActorName, Value : bool
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> TriggerMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	TArray<TObjectPtr<APuzzleActorBase>> PrevTriggerTargets;

#endif //WITH_EDITORONLY_DATA

#if WITH_EDITOR
protected:

	//TriggerTargets를 에디터에서 변경하면 Target이 되는 퍼즐 액터의 TriggerMap이 변하도록 반영하기 위한 에디터용 함수 2개
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif // WITH_EDITOR

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void SendTriggerParams(TObjectPtr<APuzzleActorBase> TriggerActor, bool Val);

	bool CheckTriggersHaveActivated() const;

#if WITH_EDITOR
	//에디터에서 TriggerMap 액터 추가 및 제거 기능
	void AddToTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToAdd);
	void RemoveFromTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToRemove);
#endif // WITH_EDITOR
};
