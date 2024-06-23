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

	//�� actor�� Ʈ���� ������ �ǰ� �ִ°�?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	bool bTriggerActive;

	//World���� Ʈ�����ϱ⸦ ���ϴ� ���͸� �����ؼ� �־����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<TObjectPtr<APuzzleActorBase>> TriggerTargets;

	//���� �� ���͸� Trigger�ϴ����� ToTrigger�� �ִ� ���Ͱ� BeginPlay()���� �߰���.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger", Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<APuzzleActorBase>> WhoTriggerThis;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//WhoTriggerThis�� Init��.
	void InitWhoTriggerThis();

public:

	bool GetTriggerActive() const;

};
