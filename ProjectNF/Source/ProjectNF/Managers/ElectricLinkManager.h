// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces.h"
#include "ElectricLinkManager.generated.h"

class UElectricLinkComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTNF_API UElectricLinkManager : public UObject, public IManageable
{
	GENERATED_BODY()
	
public:

	UElectricLinkManager();
	
	//맵 전체에 있는 electricLink들
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> ElectricLinks;

	//맵에 존재하는 root electricLink들
	//root는 전기를 생성하는 역할을 함
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> RootLinks;

	FTimerHandle ElectricLinkTimer;

	UFUNCTION(BlueprintCallable)
	void SearchAllLinks();

	UFUNCTION(BlueprintCallable)
	void LinkTest();

	virtual void ManagerInit() override;

};
