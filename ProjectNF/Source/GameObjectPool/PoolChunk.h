// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "PoolChunk.generated.h"

/**
 * Pool 가능한 오브젝트를 보관하는 청크 클래스. TQueue 사용함.
 */
UCLASS()
class GAMEOBJECTPOOL_API UPoolChunk : public UObject
{
	GENERATED_BODY()
	
protected:

	TQueue<IObjectPoolable*> PoolObjects;

public:

	TQueue<IObjectPoolable*>& GetPoolObjectQueue();

};
