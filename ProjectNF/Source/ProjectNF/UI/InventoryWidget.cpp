// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemSlotWidget.h"
#include "Components/GridPanel.h"
#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"
#include "DebugHelper.h"
#include "Components/InventoryComponent.h"
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어가 가지고 있는 인벤토리 Component를 읽는다.
	InventoryComponentRef = GetOwningPlayerPawn()->FindComponentByClass<UInventoryComponent>();

	InventoryGridPanel->ClearChildren();
	
	int32 inventorySize = 100;
	int32 startOffset = 20; //인벤토리 0~9번째는 장비칸 예약, 10~19는 퀵슬롯 예약.
	for (int32 i = startOffset; i < inventorySize; i++)
	{
		//Create
		UItemSlotWidget* slot = Cast<UItemSlotWidget>(UNFGameInstance::GetObjectManager()
			->CreateWidgetFromName(TEXT("ItemSlotWidget"), this));

		if (!IsValid(slot))
		{
			Debug::Print(DEBUG_TEXT("create slot failed"));
			continue;
		}

		int32 row = i / ColumnNum;
		int32 column = i % ColumnNum;

		InventoryGridPanel->AddChildToGrid(slot, row, column);
		ItemSlotWidgets.Add(slot);

		//TODO : Slot 초기화
		int32 slotNum = startOffset + i;

	}


	//TODO: 이 슬롯들 전부 장비로서 연결해야함.
	
	//WeaponSlot;
	//ArmorSlot;
	//ShieldSlot;
	//AccessorySlot01;
	//AccessorySlot02;

}

void UInventoryWidget::ToggleInventory()
{
	//인벤토리가 보이게 & 안보이게 Toggle하기



}
