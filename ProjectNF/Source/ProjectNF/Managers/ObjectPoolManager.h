// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces.h"
#include "DebugHelper.h"
#include "ObjectPoolManager.generated.h"

class UPoolChunk;

/**
 * ObjectPoolManager : Object Pool�� ����ϴ� �Ŵ���
 * GameMode�� ���� ����?
 * �𸮾� ���͵��� Level�� �ٲ�� ���� ������� ������ �̱����̳� GameInstance�� ����� ObjectPool�� �ϱ� �����.
 */
UCLASS()
class PROJECTNF_API UObjectPoolManager : public UObject, public IManageable
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

	virtual void ManagerInit() override;

	//Ǯ���� ������Ʈ�� ��� spawn��
	UFUNCTION(BlueprintCallable)
	AActor* SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, const FVector& Location, const FRotator& Rotation);

	//UFUNCTION()�� template�� ȣȯ���� �ʾƼ� Delegate�� ���� �� �� �Լ��� ����� �� ����.
	template <typename T>
	T* SpawnFromPool(UObject* WorldContext, TSubclassOf<T> PoolableBP, FVector Location, FRotator Rotation);


	//������Ʈ�� ȸ���Ͽ� Ǯ�� ����
	UFUNCTION(BlueprintCallable)
	void DespawnToPool(AActor* PoolableActor);


	void ClearObjectPooling();
};

template<typename T>
T* UObjectPoolManager::SpawnFromPool(UObject* WorldContext, TSubclassOf<T> PoolableBP, FVector Location, FRotator Rotation)
{
	//ObjectPoolable �������̽� üũ
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		Debug::Print(DEBUG_TEXT("not ObjectPoolable"));
		return nullptr;
	}

	//�������Ʈ Ÿ���� ������ Class�� �������� Ȯ��
	auto classKey = PoolableBP.GetDefaultObject()->GetClass();


	//�ش� Ŭ���� Ÿ���� Pool Chunk�� �������� �ʴ´ٸ�, PoolChunk ����
	if (!ObjectPoolMap.Contains(classKey))
	{
		//UE_LOG(LogTemp, Warning, TEXT("no Pool Chunk. make Pool Chunk To Spawn"));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classKey, poolChunk);
	}

	auto& objectPoolQueue = ObjectPoolMap[classKey]->GetPoolObjectQueue();
	T* poolableActor = nullptr;


	//PoolChunk�� ����ٸ� �׳� ���� ����
	if (objectPoolQueue.IsEmpty())
	{
		Debug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<T>(PoolableBP, Location, Rotation);
	}
	else //PoolChunk�� ��Ȱ��ȭ Actor�� �ִٸ�, �ش� Chunk���� �ϳ� ���� ����Ѵ�.
	{
		Debug::Print(DEBUG_TEXT("Pool Chunk Has PoolableActors."));
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		//���� ���� �� ���̰��ϱ�
		//TODO : ���� ���� ���� Ȱ��ȭ ����
		poolableActor = Cast<AActor>(ObjectPoolable);
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);

	}

	//pool ������Ʈ�� beginplay�� ����Ѵ�.
	//������ else �ڵ� �ʿ��� ���� ����� ������Ʈ�� beginplay�� ���۾���.
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);


	return poolableActor;
}
