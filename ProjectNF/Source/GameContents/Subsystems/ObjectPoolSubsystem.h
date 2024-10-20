// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Interfaces/ObjectPoolInterfaces.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class UPoolChunk;

/**
 * 언리얼 Actor는 레벨이 바뀌면 사라지기 때문에 오브젝트 풀은 월드가 유효할 때만 존재하면 되므로 world subsystem
 */
UCLASS()
class GAMECONTENTS_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	UObjectPoolSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

protected:

	//클래스 이름(BluePrint 포함)하여 클래스 단위의 key를 사용한 Map으로 만들어
	//각각의 클래스에 매칭하는 Object Pool Chunk를 관리
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pool")
	TMap<UClass*, UPoolChunk*> ObjectPoolMap;


public:

	//풀에서 오브젝트를 얻어 spawn한다.
	//이 함수로 생성되는 Actor는 IObjectPoolable을 상속받은 객체다.
	UFUNCTION(BlueprintCallable)
	AActor* SpawnInPool(UObject* WorldContext, UClass* PoolableBP, const FVector& Location, const FRotator& Rotation);

	//오브젝트를 회수하여 풀에 넣음
	UFUNCTION(BlueprintCallable)
	void DespawnToPool(AActor* PoolableActor);


	void ClearObjectPooling();

};
