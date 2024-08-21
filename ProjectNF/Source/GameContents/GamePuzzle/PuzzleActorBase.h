// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleActorBase.generated.h"

//TODO : 깨진 글자 고치기..

UCLASS(abstract)
class GAMECONTENTS_API APuzzleActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActorBase();

protected:

	//World에서 선택해야할 트리거 대상
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TObjectPtr<APuzzleActorBase>> TriggerTargets;

private:

	//TriggerTargets트리거 대상에 대한 TMap
	//key : ActorName, Value : bool
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> TriggerMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITORONLY_DATA

	//PrevTriggerTargets는 에디터에서 연결한 트리거 값의 이전 값을 저장하기 위한 배열이다.
	//이전 값을 비교하는 처리가 필요할 때만 존재하므로 WITH_EDITORONLY_DATA다.
	UPROPERTY()
	TArray<TObjectPtr<APuzzleActorBase>> PrevTriggerTargets;

#endif //WITH_EDITORONLY_DATA

#if WITH_EDITOR
protected:

	//TriggerTargets을 에디터 내에서 설정하기 위한 함수들
	//이 기능은 WITH_EDITOR가 없으면 빌드한 게임에서 오류가 난다. 그러므로 WITH_EDITOR 처리해주어야한다.
	//.cpp도 마찬가지
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

	//TriggerMap을 에디터에서 변경할 때 필요한 함수들
	void AddToTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToAdd);
	void RemoveFromTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToRemove);

#endif // WITH_EDITOR

};
