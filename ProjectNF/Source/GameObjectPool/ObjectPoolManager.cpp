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
	//ObjectPoolable 인터페이스 체크
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		Debug::Print(DEBUG_TEXT("not ObjectPoolable"));
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
		Debug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation);
	}
	else //PoolChunk에 비활성화 Actor가 있다면, 해당 Chunk에서 하나 꺼내 사용한다.
	{
		Debug::Print(DEBUG_TEXT("Pool Chunk Has PoolableActors."));
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		//위지 설정 및 보이게하기
		//TODO : 액터 관련 각종 활성화 로직
		poolableActor = Cast<AActor>(ObjectPoolable);
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);

	}

	//pool 오브젝트의 beginplay를 대신한다.
	//실제로 else 코드 쪽에서 꺼내 사용한 오브젝트는 beginplay가 동작안함.
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);
}

void UObjectPoolManager::DespawnToPool(AActor* PoolableActor)
{
	//Poolable 확인
	IObjectPoolable* objectPoolable = Cast<IObjectPoolable>(PoolableActor);
	if (!objectPoolable)
	{
		Debug::Print(DEBUG_TEXT("Not ObjectPoolable Actor."));
		return;
	}

	auto classkey = PoolableActor->GetClass();

	//PoolChunk가 존재하는지 확인. 청크가 없으면 추가한다.
	if (!ObjectPoolMap.Contains(classkey))
	{
		Debug::Print(DEBUG_TEXT("no Pool Chunk. make Pool Chunk To Despawn."));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classkey, poolChunk);
	}

	//Chunk의 Queue에 넣는다.
	ObjectPoolMap[classkey]->GetPoolObjectQueue().Enqueue(objectPoolable);

	//Pool에 넣은 것은 안보이게 한다.
	//TODO : 액터 관련 각종 비활성화
	//문제 : 안보이기만 하고 Physics가 켜져있음. 다만 오브젝트 풀링 기능 자체에 문제가 있는게 아니므로 일단 Ok
	//해결방안? : 일단 닿지 않을 위치로 이동시킨다.
	PoolableActor->SetActorHiddenInGame(true);
	PoolableActor->SetActorLocationAndRotation(FVector(-10000, -10000, 1000000), FRotator::ZeroRotator); //닿지 않을 만한 위치로 이동

	IObjectPoolable::Execute_PoolEndPlay(PoolableActor);
}

void UObjectPoolManager::ClearObjectPooling()
{
	//ObjectPool에 있는 액터들은 비활성화 상태긴해도 World가 사라지기 전에는 계속 존재함
	//만약 World가 존재하는 상황에서 ObjectPoolMap을 비워도 오브젝트들이 사라지지 않기 때문에 Clear를 따로 만듬.

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

	//!! : chunk가 필요하면 이 부분 변경할 것
	ObjectPoolMap.Empty();


}
