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

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	TArray<TObjectPtr<APuzzleActorBase>> PrevTriggerTargets;

#endif //WITH_EDITORONLY_DATA

#if WITH_EDITOR
protected:

	//TriggerTargets�� �����Ϳ��� �����ϸ� Target�� �Ǵ� ���� ������ TriggerMap�� ���ϵ��� �ݿ��ϱ� ���� �����Ϳ� �Լ� 2��
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
	//�����Ϳ��� TriggerMap ���� �߰� �� ���� ���
	void AddToTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToAdd);
	void RemoveFromTriggerMap(TObjectPtr<APuzzleActorBase> PuzzleActorToRemove);
#endif // WITH_EDITOR
};
