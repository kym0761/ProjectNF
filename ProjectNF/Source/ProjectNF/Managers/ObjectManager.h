// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "DebugHelper.h"
#include "ObjectManager.generated.h"

/**
 * ActorSpawnFactory다.
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTNF_API UObjectManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UObjectManager();

protected:

	/*
	* BP_ObjectManager에서 등록해 사용한다.
	* Key : "ClassName" ,Value : BP_SomeActor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, UClass*> BlueprintMap;

public:
	/*
	* Spawn할 때 TSubclassOf<AActor>를 거치지 않고 String으로 Spawn한다.
	* 예시)Spawn(TEXT("WantToSpawn"),Location,Rotation);
	*/
	UFUNCTION()
	AActor* Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	void Despawn(AActor* DespawnTarget);

	virtual void InitManager() override;

	void LoadBlueprints(TMap<FString, UClass*>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths);

};

