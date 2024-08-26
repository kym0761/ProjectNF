// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemShopSubsystem.generated.h"

class UShopObject;

/**
 * ItemShopSubsystem은 매 상점 이용마다 상점 상태를 저장하기 위한 서브시스템
 * 예시) 오늘 아이템을 산다. 아이템이 매진됨
 *		다음날에 매진된 아이템이 충전됨(정확히는 원래 값으로 초기화)
 * 아이템은 재고가 무한대일 수 있지만, 재고가 정해져있을 수도 있는 부분을 관리함.
 */
UCLASS()
class GAMECONTENTS_API UItemShopSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UItemShopSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:

	//key : 샵 액터 , Value : ShopObject
	UPROPERTY()
	TMap<FString, UShopObject*> ShopMap;

public:

	UShopObject* TryGetShop(FString ShopOwner);
	

};
