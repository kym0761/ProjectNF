// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "DebugHelper.h"
#include "ObjectManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTNF_API UObjectManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UObjectManager();

protected:

	//BP_ObjectManager에서 관리함.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TSubclassOf<AActor>> BlueprintMap;

public:

	UFUNCTION()
	AActor* Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	void Despawn(AActor* DespawnTarget);

	virtual void InitManager() override;

};

