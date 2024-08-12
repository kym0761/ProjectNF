// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemsChanged);
DECLARE_DELEGATE_RetVal_OneParam(FItemSheetData, FRequestItemSheetData, const FName&);

UCLASS()
class GAMECONTENTS_API UInventoryObject : public UObject
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
	int32 InventorySize = 100;

public:

	/*-------------*/
	//인벤토리 아이템 정보가 변경되면 해야할 일
	//1 인벤토리 UI 정보를 변경해야함.
	//2 맵 이동? 게임 저장 등을 고려해 정보 저장을 불러와주어야함?
	//3 기타 등등
	//주의 : 인벤토리 UI 삭제된 뒤에 문제가 생기면 이 부분에 bind된 부분을 없애야함.
	/*-------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	FOnInventoryItemsChanged OnInventoryItemsChanged;

	//TODO : 아직 InventoryObject 생성하고 이를 Set하는 기능을 안만듬. 인벤토리는 아직 동작하지 않을 것임.
	//Item Sheet Data를 얻어오는 것을 요청.
	//UPROPERTY()
	FRequestItemSheetData RequestItemSheetData;

	//0~9 : 장비칸 예약
	//10~19 : 퀵슬롯 예약
	//20~(inventorySize-1) : 아이템을 가지고 다닐 수 있는 공간
	int32 FreeInventoryStart = 20;

public:

	void InitInventory();

	void LoadInventory(const TArray<FItemSlotData>& InSlots);


	//인벤토리에 빈 공간이 있는지?
	bool HasInventoryEmptySpace() const;
	//인벤토리에 아이템이 들어갈 충분한 공간이 있는지?
	bool HasEnoughSpaceForItem(const FItemSlotData& InData) const;
	//특정 아이템을 가지고 있는지?
	bool HasItemInInventory(const FName& ItemName) const;
	//인벤토리에 있는 특정 아이템의 갯수가 충분한지?
	bool HasEnoughQuantityOfItem(const FName& ItemName, const int32 Quantity) const;
	
	//특정 위치의 아이템 정보
	const FItemSlotData* GetInventoryItem(const int32 Index) const;
	//Index 위치에 아이템 정보 Set
	bool SetInventoryItem(const int32 Index, const FItemSlotData& InData);
	//인벤토리에 아이템을 넣기
	int32 AddItemToInventory(const FItemSlotData& InData);

	//특정 위치의 아이템을 n개 쓰는 함수
	bool UseItemInInventory(const int32 ItemIndex, const int32 UseQuantity = 1);
	//인벤토리 어딘가에 특정 아이템을 n개 쓰는 함수
	bool UseItemInInventory(const FName& ItemName, const int32 UseQuantity = 1);

	//인벤토리 공간 Ref
	TArray<FItemSlotData>& GetAllItems();
	//인벤토리 Size
	int32 GetInventorySize() const;

	int32 GetFreeInventoryStart() const;

	static bool SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex);

};
