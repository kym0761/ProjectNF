// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces.h"
#include "PoolChunk.generated.h"

/**
 * Pool ������ ������Ʈ�� �����ϴ� ûũ Ŭ����. TQueue �����.
 */
UCLASS()
class GAMEOBJECTPOOL_API UPoolChunk : public UObject
{
	GENERATED_BODY()
	
private:

	//IObjectPoolable�� �������̽��� ��ӹ��� "Actor" Queue
	TQueue<IObjectPoolable*> PoolObjects;

public:

	TQueue<IObjectPoolable*>& GetPoolObjectQueue();

};
