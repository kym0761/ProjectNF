// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolChunk.h"

TQueue<IObjectPoolable*>& UPoolChunk::GetPoolObjectQueue()
{
	return PoolObjects;
}
