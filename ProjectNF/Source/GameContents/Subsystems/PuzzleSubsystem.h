// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "PuzzleSubsystem.generated.h"

class UElectricLinkComponent;

/**
 * 퍼즐도 퍼즐 액터가 월드가 존재할 동안만 유효하므로 월드 서브시스템으로 관리
 */
UCLASS()
class GAMECONTENTS_API UPuzzleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	UPuzzleSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	//맵 전체에 있는 electricLink의 모음
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> ElectricLinks;

	//맵에 존재하는 root electricLink들
	//root는 전기를 생성하는 역할을 함
	UPROPERTY()
	TSet<TObjectPtr<UElectricLinkComponent>> RootLinks;

	FTimerHandle ElectricLinkTimer;

public:

	//UFUNCTION(BlueprintCallable)
	void SearchAllLinks();

	//UFUNCTION(BlueprintCallable)
	void LinkTest();

};
