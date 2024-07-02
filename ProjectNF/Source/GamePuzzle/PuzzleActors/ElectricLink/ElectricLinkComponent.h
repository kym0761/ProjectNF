// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ElectricLinkComponent.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLinkActivatedChanged, bool, bChanged);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEPUZZLE_API UElectricLinkComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UElectricLinkComponent();

	//이 값이 true면, 무조건 Activate한다
	//ElectricPuzzleDevice에서만 값이 변경될 수 있다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	bool bRootLink;

	//인접한 LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	TSet<TObjectPtr<UElectricLinkComponent>> AdjacentLinkComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	TObjectPtr<UNiagaraSystem> ElectricNiagaraBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	FOnLinkActivatedChanged OnLinkActivatedChanged;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link", Meta = (AllowPrivateAccess = "true"))
	bool bLinkActive;

	UPROPERTY()
	FTimerHandle LinkJobTimer;

	const float LinkJobInterval = 0.5f; //LinkJob을 몇초에 1번할 것인가?

	const float ElectricEffectInterval = 0.12f; // tick에서 전기 이펙트 몇초에 1번 동작시킬 것인가?

	const float ElectricityDistance = 1000.0f;

	UPROPERTY()
	float ElectricEffectCounter = 0.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void LinkJob();

	void ElectricLinkActivate();
	void ElectricLinkDeactivate();

	void SetAsRootLink();
};
