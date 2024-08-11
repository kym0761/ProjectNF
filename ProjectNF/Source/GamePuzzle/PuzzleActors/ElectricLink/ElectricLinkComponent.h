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

	//�� ���� true��, ������ Activate�Ѵ�
	//ElectricPuzzleDevice������ ���� ����� �� �ִ�.
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

	const float LinkJobInterval = 0.5f; //LinkJob�� ���ʿ� 1���� ���ΰ�?

	const float ElectricEffectInterval = 0.12f; // tick���� ���� ����Ʈ ���ʿ� 1�� ���۽�ų ���ΰ�?

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
