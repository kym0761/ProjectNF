// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "Interfaces.h"
#include "PoolChunk.h"
#include "DebugHelper.h"

UObjectPoolManager::UObjectPoolManager()
{
}

void UObjectPoolManager::ManagerInit()
{
	ObjectPoolMap.Empty();
}

void UObjectPoolManager::SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, FVector Location, FRotator Rotation)
{
	//ObjectPoolable �������̽� üũ
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		Debug::Print(DEBUG_TEXT("not ObjectPoolable"));
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
		Debug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation);
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
}

void UObjectPoolManager::DespawnToPool(AActor* PoolableActor)
{
	//Poolable Ȯ��
	IObjectPoolable* objectPoolable = Cast<IObjectPoolable>(PoolableActor);
	if (!objectPoolable)
	{
		Debug::Print(DEBUG_TEXT("Not ObjectPoolable Actor."));
		return;
	}

	auto classkey = PoolableActor->GetClass();

	//PoolChunk�� �����ϴ��� Ȯ��. ûũ�� ������ �߰��Ѵ�.
	if (!ObjectPoolMap.Contains(classkey))
	{
		Debug::Print(DEBUG_TEXT("no Pool Chunk. make Pool Chunk To Despawn."));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classkey, poolChunk);
	}

	//Chunk�� Queue�� �ִ´�.
	ObjectPoolMap[classkey]->GetPoolObjectQueue().Enqueue(objectPoolable);

	//Pool�� ���� ���� �Ⱥ��̰� �Ѵ�.
	//TODO : ���� ���� ���� ��Ȱ��ȭ
	//���� : �Ⱥ��̱⸸ �ϰ� Physics�� ��������. �ٸ� ������Ʈ Ǯ�� ��� ��ü�� ������ �ִ°� �ƴϹǷ� �ϴ� Ok
	//�ذ���? : �ϴ� ���� ���� ��ġ�� �̵���Ų��.
	PoolableActor->SetActorHiddenInGame(true);
	PoolableActor->SetActorLocationAndRotation(FVector(-10000, -10000, 1000000), FRotator::ZeroRotator); //���� ���� ���� ��ġ�� �̵�

	IObjectPoolable::Execute_PoolEndPlay(PoolableActor);
}

void UObjectPoolManager::ClearObjectPooling()
{
	//ObjectPool�� �ִ� ���͵��� ��Ȱ��ȭ ���±��ص� World�� ������� ������ ��� ������
	//���� World�� �����ϴ� ��Ȳ���� ObjectPoolMap�� ����� ������Ʈ���� ������� �ʱ� ������ Clear�� ���� ����.

	for (auto pi : ObjectPoolMap)
	{
		UPoolChunk* chunk = pi.Value;

		auto& queue = chunk->GetPoolObjectQueue();

		while (!queue.IsEmpty())
		{
			IObjectPoolable* poolable = nullptr;
			queue.Dequeue(poolable);

			auto actor = Cast<AActor>(poolable);
			if (IsValid(actor))
			{
				actor->Destroy();
			}
		}

	}

	//!! : chunk�� �ʿ��ϸ� �� �κ� ������ ��
	ObjectPoolMap.Empty();


}
