// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolManager.generated.h"

class UPoolChunk;

/**
 * ObjectPoolManager : Object Pool을 담당하는 매니저
 * GameMode에 있을 예정?
 * 언리얼 액터들은 Level이 바뀌면 전부 사라지기 때문에 싱글톤이나 GameInstance를 사용해 ObjectPool을 하기 곤란함.
 */
UCLASS()
class GAMEOBJECTPOOL_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()

public:

	UObjectPoolManager();

protected:

	//클래스 이름(BluePrint 포함)하여 클래스 단위의 key를 사용한 Map으로 만들어
	//각각의 클래스에 매칭하는 Object Pool Chunk를 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pool")
	TMap<UClass*, UPoolChunk*> ObjectPoolMap;

public:

	//풀에서 오브젝트를 얻어 spawn함
	UFUNCTION(BlueprintCallable)
	void SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, FVector Location, FRotator Rotation);

	//오브젝트를 회수하여 풀에 넣음
	UFUNCTION(BlueprintCallable)
	void DespawnToPool(AActor* PoolableActor);


	void ClearObjectPooling();
};
