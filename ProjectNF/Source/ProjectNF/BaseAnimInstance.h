// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

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
