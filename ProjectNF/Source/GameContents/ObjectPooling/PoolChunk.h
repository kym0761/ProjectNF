// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ObjectPoolInterfaces.h"
#include "PoolChunk.generated.h"

/**
 * Pool 가능한 오브젝트를 보관하는 청크 클래스. TQueue 사용함.
 * 일단, UPoolChunk는 자신이 어떤 오브젝트를 보관하고 있는지는 전혀 모른다.
 * ObjectPoolSubsystem에서 클래스 타입을 Key로 사용해 PoolChunk를 할당받아 사용하고 있다.
 * 즉, PoolChunk의 queue에 있는 오브젝트는 전부 같은 타입이다.
 */
UCLASS()
class GAMECONTENTS_API UPoolChunk : public UObject
{
	GENERATED_BODY()
	
private:

	//IObjectPoolable을 인터페이스로 상속받은 "Actor" Queue
	TQueue<IObjectPoolable*> PoolObjects;

public:

	TQueue<IObjectPoolable*>& GetPoolObjectQueue();

};
