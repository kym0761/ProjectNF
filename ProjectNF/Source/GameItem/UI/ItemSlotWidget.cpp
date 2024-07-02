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

	//drag������, �ƴϸ� Ŭ���̾������� ���� �ൿ�� �޶���� �� ����
	//drag�� 

	return FReply::Handled();
}

void UItemSlotWidget::DragFunction(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (IsValid(ItemSlotBP))
	{
		//drag drop�� �� bp�� ����
		return;
	}

	if (!IsValid(InventoryComponentRef))
	{
		//drag�� �ʿ��� InventoryRef�� ����
		return;
	}

	if (!InventoryComponentRef->GetAllItems().IsValidIndex(InventorySlotNumber))
	{
		//Slot Number�� �ùٸ�������
		return;
	}

	//TODO : Item Database���� item ������ �����;���.
	//���� : Item Image ���� � �ʿ���

	//drag display
	TObjectPtr<UItemSlotWidget> dragDisplay = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotBP);

	if (!IsValid(dragDisplay))
	{
		//drag display ���� ����
		return;
	}

	//TODO : function���� ���� �ʿ䰡 ����
	dragDisplay->InventoryComponentRef = InventoryComponentRef;
	dragDisplay->InventorySlotNumber = InventorySlotNumber;
	//dragDisplay->UpdateItemSlotWidget();

	//drag drop operation
	//? new object�� outer�� �������� �ʾ����Ƿ� 
	// �� �ð����� �巡�׸� �����ϰ� ������ Garbage Collection�Ǵ� ������ ������?
	//Ȥ�� ���߿� ���� ����� ���� ��ġ�� �� �������� ��
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
		//�߸��� InOperation
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
			//TODO : �κ��丮 ������Ʈ?
			return true;
		}
	}

	return false;
}
