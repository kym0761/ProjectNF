// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolManager.generated.h"

class UPoolChunk;

/**
 * ObjectPoolManager : Object Pool�� ����ϴ� �Ŵ���
 * GameMode�� ���� ����?
 * �𸮾� ���͵��� Level�� �ٲ�� ���� ������� ������ �̱����̳� GameInstance�� ����� ObjectPool�� �ϱ� �����.
 */
UCLASS()
class GAMEOBJECTPOOL_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()

public:

	UObjectPoolManager();

protected:

	//Ŭ���� �̸�(BluePrint ����)�Ͽ� Ŭ���� ������ key�� ����� Map���� �����
	//������ Ŭ������ ��Ī�ϴ� Object Pool Chunk�� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pool")
	TMap<UClass*, UPoolChunk*> ObjectPoolMap;

public:

	//Ǯ���� ������Ʈ�� ��� spawn��
	UFUNCTION(BlueprintCallable)
	void SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, FVector Location, FRotator Rotation);

	//������Ʈ�� ȸ���Ͽ� Ǯ�� ����
	UFUNCTION(BlueprintCallable)
	void DespawnToPool(AActor* PoolableActor);


	void ClearObjectPooling();
};
