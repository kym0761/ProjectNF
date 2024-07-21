// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFGameModeBase.generated.h"

class UGridManager;
class UElectricLinkManager;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Managers", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UElectricLinkManager> ElectricLinkManager;

	static TObjectPtr<UElectricLinkManager> GElectricLinkManager;

	FTimerHandle ElectricLinkTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
