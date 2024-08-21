// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ObjectPoolInterfaces.h"
#include "PoolChunk.generated.h"

/**
 * Pool 가능한 오브젝트를 보관하는 청크 클래스. TQueue 사용함.
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
