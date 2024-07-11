// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "PoolChunk.generated.h"

/**
 * Pool ������ ������Ʈ�� �����ϴ� ûũ Ŭ����. TQueue �����.
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
