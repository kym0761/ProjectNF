// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSubsystem.h"
#include "GameFramework/MovementComponent.h"
#include "DebugHelper.h"
#include "ObjectPooling/PoolChunk.h"

UObjectPoolSubsystem::UObjectPoolSubsystem()
{
}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UObjectPoolSubsystem::Deinitialize()
{
	Super::Deinitialize();

	////지금 필요없어서 비활성화
	//ClearObjectPooling();
}

AActor* UObjectPoolSubsystem::SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation)
{
	AActor* poolableActor = nullptr;

	//ObjectPoolable 인터페이스 체크
	bool bCheckObjectPoolable = PoolableBP->GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		FMyDebug::Print(DEBUG_TEXT("not ObjectPoolable"));
		return nullptr;
	}

	//블루프린트 타입을 포함한 Class가 무엇인지 확인
	UClass* classKey = PoolableBP->GetDefaultObject()->GetClass();

	//해당 클래스 타입의 Pool Chunk가 존재하지 않는다면, PoolChunk 생성
	if (!ObjectPoolMap.Contains(classKey))
	{
		//UE_LOG(LogTemp, Warning, TEXT("no Pool Chunk. make Pool Chunk To Spawn"));
		UPoolChunk* poolChunk = NewObject<UPoolChunk>(this);
		ObjectPoolMap.Add(classKey, poolChunk);
	}

	auto& objectPoolQueue = ObjectPoolMap[classKey]->GetPoolObjectQueue();

	//PoolChunk가 비었다면 그냥 새로 생성
	if (objectPoolQueue.IsEmpty())
	{
		//충돌을 무시하고 무조건 spawn함
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		poolableActor = WorldContext->GetWorld()->SpawnActor<AActor>(PoolableBP, Location, Rotation, spawnParam);
	
		//FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
	}
	else //PoolChunk에 비활성화 Actor가 있다면, 해당 Chunk에서 하나 꺼내 사용한다.
	{
		IObjectPoolable* ObjectPoolable = nullptr;
		objectPoolQueue.Dequeue(ObjectPoolable);

		poolableActor = Cast<AActor>(ObjectPoolable);
		if (!IsValid(poolableActor))
		{
			//Cast 실패?
			return nullptr;
		}

		//PoolActor 활성화
		//위치 설정
		//Visibility 활성
		//Collision 활성
		//Movement Component가 있을 시 활성화
		poolableActor->SetActorLocationAndRotation(Location, Rotation);
		poolableActor->SetActorHiddenInGame(false);
		poolableActor->SetActorEnableCollision(true);

		UMovementComponent* movement = poolableActor->FindComponentByClass<UMovementComponent>();
		if (IsValid(movement))
		{
			movement->Activate();
		}

		//FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has PoolableActors."));
	}

	//pool 오브젝트의 Actor::BeginPlay()를 대신한다.
	//ObjectPooling을 사용한 Actor는 Spawn될 때 BeginPlay() 동작하지 않기 때문에 따로 구현
	IObjectPoolable::Execute_PoolBeginPlay(poolableActor);

	return poolableActor;
}

void UObjectPoolSubsystem::DespawnToPool(AActor* PoolableActor)
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

void UObjectPoolSubsystem::ClearObjectPooling()
{
	//오브젝트 풀 전체를 비우는 기능

	//ObjectPool에 있는 액터들은 사용자(개발자)에 의도대로 비활성화 상태이므로, Level이 바뀌지 않는 이상 계속 유지됨.
	
	//Level이 바뀌면서 -> ObjectPoolSubsystem 삭제 -> Chunk 삭제 -> 오브젝트(Actor) 삭제
	//가 일어나서 알아서 삭제는 되겠지만, 일단 과거에 만들어놓았던 방식은 내가 일일이 삭제해야 했음.
	//지금은 일단 필요는 없지만, 혹시나 가비지 컬렉션 문제가 여기서 일어난다면 이를 활성화하기.
	
	//Chunk 안의 오브젝트 Ref 삭제 & Chunk Ref 삭제만 하면 언리얼 가비지 컬렉션에 의해 알아서 삭제될 것으로 예상함.
	for (auto pi : ObjectPoolMap)
	{
		UPoolChunk* chunk = pi.Value;

		TQueue<IObjectPoolable*>& queue = chunk->GetPoolObjectQueue();
		queue.Empty();
	}

	ObjectPoolMap.Empty();
}
