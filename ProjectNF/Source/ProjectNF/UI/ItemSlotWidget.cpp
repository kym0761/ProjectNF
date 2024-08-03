// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "DebugHelper.h"
//#include "InventoryComponent.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//Drag Function Activate.
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return reply.NativeReply;
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	DragFunction(InGeometry, InMouseEvent, OutOperation);

}

bool UItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool dropResult = DropFunction(InGeometry, InDragDropEvent, InOperation);

	return dropResult;
}

FReply UItemSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	//drag였는지, 아니면 클릭이었는지에 따라 행동이 달라야함.

	//클릭이었으면 아이템 사용 요청
	//drag였으면 아이템 슬롯끼리 정보 교체

	return FReply::Handled();
}

void UItemSlotWidget::DragFunction(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Debug::Print(DEBUG_TEXT("Item Slot Drag Function"));



	//if (!IsValid(InventoryComponentRef))
	//{
	//	//drag에 필요한 InventoryRef가 없음
	//	return;
	//}

	////if (!InventoryComponentRef->GetAllItems().IsValidIndex(InventorySlotNumber))
	////{
	////	//Slot Number가 올바르지않음
	////	return;
	////}

	////TODO : Item Database에서 item 정보를 가져와야함.
	////이유 : Item Image 세팅 등에 필요함

	////drag display
	TObjectPtr<UItemSlotWidget> dragDisplay = Cast<UItemSlotWidget>(
		UNFGameInstance::GetObjectManager()->CreateWidgetFromName(TEXT("ItemSlotWidget"), GetOwningPlayer()));

	if (!IsValid(dragDisplay))
	{
		//drag display 생성 실패
		Debug::Print(DEBUG_TEXT("Create Drag Display Failed."));
			return;
	}

	////TODO : function으로 줄일 필요가 있음
	//dragDisplay->InventoryComponentRef = InventoryComponentRef;
	//dragDisplay->InventorySlotNumber = InventorySlotNumber;
	////dragDisplay->UpdateItemSlotWidget();

	//drag drop operation
	TObjectPtr<UDragDropOperation> dragdropOper = NewObject<UDragDropOperation>(); // outer?
	dragdropOper->Payload = this;
	dragdropOper->DefaultDragVisual = dragDisplay;
	dragdropOper->Pivot = EDragPivot::CenterCenter;

	//OutOperation에 dragdropOper를 주어야 실제 drag slot이 생성
	OutOperation = dragdropOper;
}

bool UItemSlotWidget::DropFunction(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Debug::Print(DEBUG_TEXT("Item Slot Drop Function"));

	if (!IsValid(InOperation))
	{
		//잘못된 InOperation
		Debug::Print(DEBUG_TEXT("InOperation is Invalid."));
		return false;
	}

	TObjectPtr<UItemSlotWidget> droppedItemSlot = Cast<UItemSlotWidget>(InOperation->Payload);

	if (!IsValid(droppedItemSlot))
	{
		//dropped item slot nullptr
		Debug::Print(DEBUG_TEXT("droppedItemSlot is Invalid."));
		return false;
	}

	//int32 dropped_SlotNumber = droppedItemSlot->InventorySlotNumber;
	//TObjectPtr<UInventoryComponent> dropped_InventoryComponent = droppedItemSlot->InventoryComponentRef;

	////if (IsValid(dropped_InventoryComponent) && IsValid(InventoryComponentRef))
	////{
	////	//bool bSucceed = UInventoryComponent::SwapItemBetweenInventory(
	////	//	dropped_InventoryComponent, dropped_SlotNumber,
	////	//	InventoryComponentRef, InventorySlotNumber);

	////	//if (bSucceed)
	////	//{
	////	//	//TODO : 인벤토리 업데이트?
	////	//	return true;
	////	//}
	////}

	//임시로 droppedItemSlot이 정상적으로 동작하면 true로 설정.
	if(IsValid(droppedItemSlot))
	{
		Debug::Print(DEBUG_TEXT("Test OK."));
		return true;
	}
	

	//
	Debug::Print(DEBUG_TEXT("Test Fail."));
	return false;
}
