// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "PoolChunk.h"

UObjectPoolManager::UObjectPoolManager()
{
}

void UObjectPoolManager::SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, FVector Location, FRotator Rotation)
{
	//ObjectPoolable üũ
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		//UE_LOG(LogTemp, Warning, TEXT("not ObjectPoolable"));
		return;
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
	AActor* poolableActor = nullptr;
	//PoolChunk�� ����ٸ� �׳� ���� ����
	if (objectPoolQueue.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation);
	}
	else //PoolChunk�� ���� �ִٸ�, �ش� Chunk���� �ϳ� ���� ����Ѵ�.
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pool Chunk Has many PoolableActors. Use it"));
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		//���� ���� �� ���̰��ϱ�
		poolableActor = Cast<AActor>(ObjectPoolable);
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);

	}

	//pool ������Ʈ�� beginplay�� ����Ѵ�.
	//������ else �ڵ� �ʿ��� ���� ����� ������Ʈ�� beginplay�� ���۾���.
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);
}

void UObjectPoolManager::DespawnToPool(AActor* PoolableActor)
{
	//Poolable Ȯ��
	IObjectPoolable* objectPoolable = Cast<IObjectPoolable>(PoolableActor);
	if (!objectPoolable)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Not ObjectPoolable Actor"));
		return;
	}

	auto classkey = PoolableActor->GetClass();

	//PoolChunk�� �����ϴ��� Ȯ��. ûũ�� ������ �߰��Ѵ�.
	if (!ObjectPoolMap.Contains(classkey))
	{
		//UE_LOG(LogTemp, Warning, TEXT("no Pool Chunk. make Pool Chunk To Despawn"));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classkey, poolChunk);
	}

	//Chunk�� Queue�� �ִ´�.
	ObjectPoolMap[classkey]->GetPoolObjectQueue().Enqueue(objectPoolable);

	//Pool�� ���� ���� �Ⱥ��̰� �Ѵ�.
	//���� : �Ⱥ��̱⸸ �ϰ� Physics�� ��������.
	//�ٸ� ������Ʈ Ǯ�� ��� ��ü�� ������ �ִ°� �ƴϹǷ� �ϴ� Ok
	PoolableActor->SetActorHiddenInGame(true);

}
