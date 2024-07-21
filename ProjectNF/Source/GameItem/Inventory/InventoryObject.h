// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/NoExportTypes.h"
#include "InventoryObject.generated.h"

/**
 * 객체별로 존재하는 인벤토리 오브젝트
 * 유닛의 인벤토리 0~9번은 장비칸으로 사용?
 * 유닛의 인벤토리 10~??번은 보관용 인벤토리로 사용?
 * 창고는 자체적으로 큰 인벤토리를 사용?
 * 
 * Enemy는 그냥 drop테이블 등을 사용하여 아이템 드랍만 함?
 */
UCLASS()
class GAMEITEM_API UInventoryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UInventoryObject();

protected:
	//인벤토리에 들어간 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlotData> Items;

	//인벤토리 사이즈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 30;

public:

	void InitInventory();

	static bool SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex);

};
