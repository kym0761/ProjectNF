// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "PoolChunk.h"

UObjectPoolManager::UObjectPoolManager()
{
}

void UObjectPoolManager::SpawnInPool(UObject* WorldContext, TSubclassOf<AActor> PoolableBP, FVector Location, FRotator Rotation)
{
	//ObjectPoolable 체크
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		//UE_LOG(LogTemp, Warning, TEXT("not ObjectPoolable"));
		return;
	}

	//블루프린트 타입을 포함한 Class가 무엇인지 확인
	auto classKey = PoolableBP.GetDefaultObject()->GetClass();

	//해당 클래스 타입의 Pool Chunk가 존재하지 않는다면, PoolChunk 생성
	if (!ObjectPoolMap.Contains(classKey))
	{
		//UE_LOG(LogTemp, Warning, TEXT("no Pool Chunk. make Pool Chunk To Spawn"));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classKey, poolChunk);
	}

	auto& objectPoolQueue = ObjectPoolMap[classKey]->GetPoolObjectQueue();
	AActor* poolableActor = nullptr;
	//PoolChunk가 비었다면 그냥 새로 생성
	if (objectPoolQueue.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation);
	}
	else //PoolChunk에 무언가 있다면, 해당 Chunk에서 하나 꺼내 사용한다.
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pool Chunk Has many PoolableActors. Use it"));
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		//위지 설정 및 보이게하기
		poolableActor = Cast<AActor>(ObjectPoolable);
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);

	}

	//pool 오브젝트의 beginplay를 대신한다.
	//실제로 else 코드 쪽에서 꺼내 사용한 오브젝트의 beginplay가 동작안함.
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);
}

void UObjectPoolManager::DespawnToPool(AActor* PoolableActor)
{
	//Poolable 확인
	IObjectPoolable* objectPoolable = Cast<IObjectPoolable>(PoolableActor);
	if (!objectPoolable)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Not ObjectPoolable Actor"));
		return;
	}

	auto classkey = PoolableActor->GetClass();

	//PoolChunk가 존재하는지 확인. 청크가 없으면 추가한다.
	if (!ObjectPoolMap.Contains(classkey))
	{
		//UE_LOG(LogTemp, Warning, TEXT("no Pool Chunk. make Pool Chunk To Despawn"));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classkey, poolChunk);
	}

	//Chunk의 Queue에 넣는다.
	ObjectPoolMap[classkey]->GetPoolObjectQueue().Enqueue(objectPoolable);

	//Pool에 넣은 것은 안보이게 한다.
	//문제 : 안보이기만 하고 Physics가 켜져있음.
	//다만 오브젝트 풀링 기능 자체에 문제가 있는게 아니므로 일단 Ok
	PoolableActor->SetActorHiddenInGame(true);

}
