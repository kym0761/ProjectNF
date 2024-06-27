// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ElectricLinkManager.generated.h"

class UElectricLinkComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEPUZZLE_API UElectricLinkManager : public UObject
{
	GENERATED_BODY()
	
public:

	UElectricLinkManager();
	
	//�� ��ü�� �ִ� electricLink��
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> ElectricLinks;

	//�ʿ� �����ϴ� root electricLink��
	//root�� ���⸦ �����ϴ� ������ ��
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> RootLinks;

	UFUNCTION(BlueprintCallable)
	void SearchAllLinks();

	UFUNCTION(BlueprintCallable)
	void LinkTest();

};
