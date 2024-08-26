// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemSlotWidget.h"
#include "Components/GridPanel.h"
//#include "System/NFGameInstance.h"
//#include "Managers/ObjectManager.h"

#include "Subsystems/ObjectSubsystem.h"
#include "DebugHelper.h"
#include "GameItem/Inventory/InventoryComponent.h"
#include "GameItem/Inventory/InventoryObject.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어가 가지고 있는 인벤토리 Component를 읽는다.

	SetInventoryComponentRef(GetOwningPlayerPawn()->FindComponentByClass<UInventoryComponent>());

	if (!IsValid(InventoryComponentRef))
	{
		FMyDebug::Print(DEBUG_TEXT("Inventory Comp Ref is Invalid."));
		return;
	}

	auto objectSubsystem = GEngine->GetEngineSubsystem<UObjectSubsystem>();
	InventoryGridPanel->ClearChildren();
	
	int32 inventorySize = InventoryComponentRef->GetInventoryObjectRef()->GetInventorySize();
	int32 startOffset = InventoryComponentRef->GetInventoryObjectRef()->GetFreeInventoryStart(); //인벤토리 0~9번째는 장비칸 예약, 10~19는 퀵슬롯 예약. 즉 20부터 시작함.
	for (int32 i = startOffset; i < inventorySize; i++)
	{
		//Create
		UItemSlotWidget* slot = Cast<UItemSlotWidget>(
			objectSubsystem->CreateWidgetBlueprint(TEXT("ItemSlotWidget"), GetOwningPlayer()));

		if (!IsValid(slot))
		{
			FMyDebug::Print(DEBUG_TEXT("create slot failed"));
			continue;
		}

		int32 row = (i - startOffset) / ColumnNum;
		int32 column = (i - startOffset) % ColumnNum;

		InventoryGridPanel->AddChildToGrid(slot, row, column);
		ItemSlotWidgets.Add(slot);

		int32 slotNum = i;
		slot->SetSlotInfo(InventoryComponentRef, slotNum);
	}


	//TODO: 이 슬롯들 전부 장비로서 연결해야함.
	
	//각각 0,1,2,3,4 index

	WeaponSlot->SetSlotInfo(InventoryComponentRef,0);
	ArmorSlot->SetSlotInfo(InventoryComponentRef, 1);
	ShieldSlot->SetSlotInfo(InventoryComponentRef,2);
	AccessorySlot01->SetSlotInfo(InventoryComponentRef, 3);
	AccessorySlot02->SetSlotInfo(InventoryComponentRef, 4);

	UpdateInventoryUI();

}

void UInventoryWidget::ToggleInventory()
{
	//인벤토리가 보이게 & 안보이게 Toggle하기



}

void UInventoryWidget::SetInventoryComponentRef(UInventoryComponent* RefVal)
{
	InventoryComponentRef = RefVal;

	InventoryComponentRef->GetInventoryObjectRef()
		->OnInventoryItemsChanged.AddDynamic(this, &UInventoryWidget::UpdateInventoryUI);
}

void UInventoryWidget::UpdateInventoryUI()
{
	for (auto i : ItemSlotWidgets)
	{
		i->UpdateSlot();
	}

	WeaponSlot->UpdateSlot();
	ArmorSlot->UpdateSlot();
	ShieldSlot->UpdateSlot();
	AccessorySlot01->UpdateSlot();
	AccessorySlot02->UpdateSlot();
}
