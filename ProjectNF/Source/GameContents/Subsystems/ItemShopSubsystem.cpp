// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemShopSubsystem.h"
#include "GameItem/Shop/ShopObject.h"
#include "DebugHelper.h"


UItemShopSubsystem::UItemShopSubsystem()
{

}

void UItemShopSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UItemShopSubsystem::Deinitialize()
{
}

UShopObject* UItemShopSubsystem::TryGetShop(FString ShopOwner)
{
	if (ShopOwner.IsEmpty())
	{
		//잘못된 접근
		//ShopOwner가 ""임
		return nullptr;
	}

	if (ShopMap.Num() == 0 || !ShopMap.Contains(ShopOwner))
	{
		UShopObject* shopObj = NewObject<UShopObject>(this);

		//TODO : ShopObject 초기화
		//매일? 일주일? 한달?마다 파는 아이템이 다를 수도 있다.
		//최초 생성시 ShopTable 값을 보고 아이템 판매 목록을 초기화해야함.

		ShopMap.Add(ShopOwner, shopObj);
		FMyDebug::Print(DEBUG_VATEXT(TEXT("Shop Created -> ShopOwner : %s"), *ShopOwner));
	}
	else
	{
		//이미 존재함.
		//아이템 판매 목록은 매일 갱신될 것이므로,
		//여기에 접근했다면 아직 하루가 지나지 않아 Shop객체가 존재하여 기존 Shop을 이용함.

		FMyDebug::Print(DEBUG_VATEXT(TEXT("Shop Exist -> ShopOwner : %s"), *ShopOwner));
	}


	return ShopMap[ShopOwner];
}
