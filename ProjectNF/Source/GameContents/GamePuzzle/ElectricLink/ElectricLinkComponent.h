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
class GAMECONTENTS_API UElectricLinkComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
	UElectricLinkComponent();

	//이 값이 true면, 상시 Activate동작한다.
	//ElectricPuzzleDevice가 Root일 때 true가 된다..
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
	bool bRootLink;

	//������ LinkComponents.
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

	const float LinkJobInterval = 0.5f; //LinkJob 주기를 얼마나 할 것인가?

	const float ElectricEffectInterval = 0.12f; // 전기 이펙트를 tick 속에서 주기를 얼마나 할 것인가?

	const float ElectricityDistance = 1000.0f; // 어느 거리에 있는 Link와 상호작용할 것인가?

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
