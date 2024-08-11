// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndAbility);

/**
 * 
 */
UCLASS()
class PROJECTNF_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UBaseAnimInstance();

protected:

	const int32 ComboNumberMin = 1;
	const int32 comboNumberMax = 6;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	int32 ComboNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> BaseCombatMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	bool bAttackPlayOK;
	
	//BP_Ability_MainCharacter일 때, "MainCharacter"부분이다.
	UPROPERTY()
	FString AbilitySuffix;

	UPROPERTY()
	FOnStartAbility OnStartAbility;

	UPROPERTY()
	FOnEndAbility OnEndAbility;

protected:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION()
	void OnCombatMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:

	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackComboOk();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	

public:

	void PlayAttackMontage();

};
