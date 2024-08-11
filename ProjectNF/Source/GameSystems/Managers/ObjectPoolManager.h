// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "Defines/Interfaces/ObjectPoolInterfaces.h"
#include "DebugHelper.h"
#include "ObjectPoolManager.generated.h"

class UPoolChunk;

/**
 * ObjectPoolManager : Object Pool을 담당하는 매니저
 * 언리얼 액터들은 Level이 바뀌면 전부 사라지기 때문에 Level이 바뀌면 Reset해주어야함.
 */
UCLASS(BlueprintType, Blueprintable)
class GAMESYSTEMS_API UObjectPoolManager : public UObject, public IManageable
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

	virtual void InitManager() override;

	//풀에서 오브젝트를 얻어 spawn한다.
	//이 함수로 생성되는 Actor는 IObjectPoolable을 상속받은 객체다.
	UFUNCTION(BlueprintCallable)
	AActor* SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation);

	//오브젝트를 회수하여 풀에 넣음
	UFUNCTION(BlueprintCallable)
	void DespawnToPool(AActor* PoolableActor);


	void ClearObjectPooling();

#pragma region DoNotUse
private:

	//UFUNCTION()과 template가 호환되지 않아서 Delegate에 붙일 때 이 함수를 사용할 수 없음.
	template <typename T>
	T* SpawnFromPool(UObject* WorldContext, TSubclassOf<T> PoolableBP, FVector Location, FRotator Rotation);
#pragma endregion
};

#pragma region NotUse

template<typename T>
T* UObjectPoolManager::SpawnFromPool(UObject* WorldContext, TSubclassOf<T> PoolableBP, FVector Location, FRotator Rotation)
{
	//ObjectPoolable 인터페이스 체크
	bool bCheckObjectPoolable = PoolableBP.GetDefaultObject()->Implements<UObjectPoolable>();
	if (!bCheckObjectPoolable)
	{
		FMyDebug::Print(DEBUG_TEXT("not ObjectPoolable"));
		return nullptr;
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
	T* poolableActor = nullptr;


	//PoolChunk가 비었다면 그냥 새로 생성
	if (objectPoolQueue.IsEmpty())
	{
		FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has not a PoolableActor. spawn new"));
		poolableActor = WorldContext->GetWorld()->SpawnActor<T>(PoolableBP, Location, Rotation);
	}
	else //PoolChunk에 비활성화 Actor가 있다면, 해당 Chunk에서 하나 꺼내 사용한다.
	{
		FMyDebug::Print(DEBUG_TEXT("Pool Chunk Has PoolableActors."));
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


	return poolableActor;
}

#pragma endregion