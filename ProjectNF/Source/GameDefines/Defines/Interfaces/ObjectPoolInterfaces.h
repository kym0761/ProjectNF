// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolInterfaces.generated.h"


 /**
  * ObjectPool이 가능하려면 IObjectPoolable을 Actor에 적용해야함.
  */

UINTERFACE(Blueprintable)
class GAMEDEFINES_API UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

//ObjectPool이 가능한 Actor의 인터페이스.
//ObjectPool에서 꺼내온 Actor들은 실제론 생성 및 삭제되지 않아 BeginPlay() EndPlay() 등이 동작하지 않으므로
//Pool용 함수들을 만들어 동작시킨다.
class GAMEDEFINES_API IObjectPoolable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PoolBeginPlay();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PoolEndPlay();

};


