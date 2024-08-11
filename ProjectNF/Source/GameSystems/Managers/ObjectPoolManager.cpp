// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "ObjectPooling/PoolChunk.h"
#include "DebugHelper.h"

#include "Kismet/GameplayStatics.h"

#include "GameFramework/MovementComponent.h"

UObjectPoolManager::UObjectPoolManager()
{
}

void UObjectPoolManager::InitManager()
{
	ClearObjectPooling();

	//ObjectPoolMap.Empty();
}

AActor* UObjectPoolManager::SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation)
{
	//ObjectPoolable 인터페이스 체크
	bool bCheckObjectPoolable = PoolableBP->GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		FMyDebug::Print(DEBUG_TEXT("not ObjectPoolable"));
		return nullptr;
	}

	//블루프린트 타입을 포함한 Class가 무엇인지 확인
	auto classKey = PoolableBP->GetDefaultObject()->GetClass();

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
		//충돌을 무시하고 무조건 spawn함
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation, spawnParam);
	}
	else //PoolChunk에 비활성화 Actor가 있다면, 해당 Chunk에서 하나 꺼내 사용한다.
	{
		FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has PoolableActors."));
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		//PoolActor 활성화
		//위치 설정
		//Visibility 활성
		//Collision 활성
		//Movement Component가 있을 시 활성화
		poolableActor = Cast<AActor>(ObjectPoolable);
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);
		poolableActor->SetActorEnableCollision(true);

		UMovementComponent* movement= poolableActor->FindComponentByClass<UMovementComponent>();
		if (IsValid(movement))
		{
			movement->Activate();
		}
	}

	//pool 오브젝트의 beginplay를 대신한다.
	//실제로 else 코드 쪽에서 꺼내 사용한 오브젝트는 beginplay가 동작안함.
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);

	return poolableActor;
}

void UObjectPoolManager::DespawnToPool(AActor* PoolableActor)
{
	//Poolable 확인
	IObjectPoolable* objectPoolable = Cast<IObjectPoolable>(PoolableActor);
	if (!objectPoolable)
	{
		FMyDebug::Print(DEBUG_TEXT("Not ObjectPoolable Actor."));
		return;
	}

	auto classkey = PoolableActor->GetClass();

	//PoolChunk가 존재하는지 확인. 청크가 없으면 추가한다.
	if (!ObjectPoolMap.Contains(classkey))
	{
		FMyDebug::Print(DEBUG_TEXT("no Pool Chunk. make Pool Chunk To Despawn."));
		auto poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classkey, poolChunk);
	}

	//Chunk의 Queue에 넣는다.
	ObjectPoolMap[classkey]->GetPoolObjectQueue().Enqueue(objectPoolable);

	//Pool에 넣은 것은 안보이게 한다.
	//보이지 않게 한다
	//닿지 않을 위치로 이동시킨다.
	//collision을 끈다.
	//movement component가 있다면 비활성화한다.
	PoolableActor->SetActorLocationAndRotation(FVector(-10000, -10000, 1000000), FRotator::ZeroRotator); //닿지 않을 만한 위치로 이동
	PoolableActor->SetActorHiddenInGame(true);
	PoolableActor->SetActorEnableCollision(false);

	UMovementComponent* movement = PoolableActor->FindComponentByClass<UMovementComponent>();
	if (IsValid(movement))
	{
		movement->Deactivate();
	}

	IObjectPoolable::Execute_PoolEndPlay(PoolableActor);

	FMyDebug::Print(DEBUG_TEXT("ObjectPoolable Actor Despawned."));

}

void UObjectPoolManager::ClearObjectPooling()
{
	//ObjectPool에 있는 액터들은 비활성화 상태긴해도 World가 사라지기 전에는 계속 존재함
	//만약 World를 변경하지 않는 상태에서 ObjectPoolMap을 비워도 오브젝트들이 사라지지 않기 때문에 Clear를 따로 만듬.

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
