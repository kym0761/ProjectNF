// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFGameModeBase.generated.h"

class UGridManager;

/**
 * GameModeBase�� Manager���� �߰��ϸ�, ���Ӹ�忡�� Manager�� ���� ������.
 */
UCLASS()
class PROJECTNF_API ANFGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ANFGameModeBase();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGridManager> GridManager;

	static TObjectPtr<UGridManager> GGridManager;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	static 	TObjectPtr<UGridManager> GetGridManager();
};
