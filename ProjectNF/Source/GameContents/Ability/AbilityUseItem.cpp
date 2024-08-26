// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityUseItem.h"
#include "DebugHelper.h"

AAbilityUseItem::AAbilityUseItem()
{

}

void AAbilityUseItem::InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal)
{
	if (!IsValid(AbilityOwnerVal))
	{
		FMyDebug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;
	AbilityData = AbilityDataVal;


	StartAbility();
}

void AAbilityUseItem::StartAbility_Implementation()
{
	FMyDebug::Print(DEBUG_TEXT("Use Item Ability ON"));

	if (RequestSpawnNiagara.IsBound())
	{
		RequestSpawnNiagara.Execute(AbilityData.AbilityNiagara,AbilityOwner->GetActorLocation(), FRotator::ZeroRotator);
	}

	//TODO : Owner나 Target에게 실제로 아이템의 효과를 발동시켜주기
	//먹으면 HP 회복 등



	EndAbility();
}

void AAbilityUseItem::EndAbility_Implementation()
{
	FMyDebug::Print(DEBUG_TEXT("Use Item Ability Off"));


	RequestDespawnAbility.ExecuteIfBound(this);
}
