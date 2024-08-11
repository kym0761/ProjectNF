// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/AbilityBase.h"
#include "AbilityCapsuleOverlap.generated.h"

class UCapsuleComponent;

/**
 * 사용예시) 무기에 붙여 닿은 적에게 데미지를 준다.
 */
UCLASS()
class GAMECONTENTS_API AAbilityCapsuleOverlap : public AAbilityBase
{
	GENERATED_BODY()
	
public:

	AAbilityCapsuleOverlap();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	virtual void InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal = nullptr) override;

	
	//어빌리티 시작하기
	virtual void StartAbility_Implementation() override;

	//어빌리티 끝마치기
	virtual void EndAbility_Implementation() override;

	//Capsule과 오버랩된 액터와 상호작용함.
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
