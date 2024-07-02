// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"

#include "Inventory/InventoryComponent.h"

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

	//drag였는지, 아니면 클릭이었는지에 따라 행동이 달라야할 수 있음
	//drag면 

	return FReply::Handled();
}

void UItemSlotWidget::DragFunction(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (IsValid(ItemSlotBP))
	{
		//drag drop에 쓸 bp가 없음
		return;
	}

	if (!IsValid(InventoryComponentRef))
	{
		//drag에 필요한 InventoryRef가 없음
		return;
	}

	if (!InventoryComponentRef->GetAllItems().IsValidIndex(InventorySlotNumber))
	{
		//Slot Number가 올바르지않음
		return;
	}

	//TODO : Item Database에서 item 정보를 가져와야함.
	//이유 : Item Image 세팅 등에 필요함

	//drag display
	TObjectPtr<UItemSlotWidget> dragDisplay = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotBP);

	if (!IsValid(dragDisplay))
	{
		//drag display 생성 실패
		return;
	}

	//TODO : function으로 줄일 필요가 있음
	dragDisplay->InventoryComponentRef = InventoryComponentRef;
	dragDisplay->InventorySlotNumber = InventorySlotNumber;
	//dragDisplay->UpdateItemSlotWidget();

	//drag drop operation
	//? new object에 outer를 설정하지 않았으므로 
	// 긴 시간동안 드래그를 진행하고 있으면 Garbage Collection되는 위험은 없을지?
	//혹시 나중에 문제 생기면 여기 고치는 게 좋을지도 모름
	TObjectPtr<UDragDropOperation> dragdropOper = NewObject<UDragDropOperation>(); // outer?
	dragdropOper->Payload = this;
	dragdropOper->DefaultDragVisual = dragDisplay;
	dragdropOper->Pivot = EDragPivot::CenterCenter;

	OutOperation = dragdropOper;
}

bool UItemSlotWidget::DropFunction(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (!IsValid(InOperation))
	{
		//잘못된 InOperation
		return false;
	}

	TObjectPtr<UItemSlotWidget> droppedItemSlot = Cast<UItemSlotWidget>(InOperation->Payload);

	if (!IsValid(droppedItemSlot))
	{
		//dropped item slot nullptr
		return false;
	}

	int32 dropped_SlotNumber = droppedItemSlot->InventorySlotNumber;
	TObjectPtr<UInventoryComponent> dropped_InventoryComponent = droppedItemSlot->InventoryComponentRef;

	if (IsValid(dropped_InventoryComponent) && IsValid(InventoryComponentRef))
	{
		bool bSucceed = UInventoryComponent::SwapItemBetweenInventory(
			dropped_InventoryComponent, dropped_SlotNumber,
			InventoryComponentRef, InventorySlotNumber);

		if (bSucceed)
		{
			//TODO : 인벤토리 업데이트?
			return true;
		}
	}

	return false;
}
