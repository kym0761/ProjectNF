// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "DebugHelper.h"

#include "Components/InventoryComponent.h"
#include "GameItem/Inventory/InventoryObject.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"
#include "Managers/DataManager.h"

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
	FMyDebug::Print(DEBUG_TEXT("Item Slot Drag Function"));

	if (!IsValid(InventoryComponentRef))
	{
		//drag에 필요한 InventoryRef가 없음
		return;
	}

	////TODO : Item Database에서 item 정보를 가져와야함.
	////이유 : Item Image 세팅 등에 필요함

	////drag display
	TObjectPtr<UItemSlotWidget> dragDisplay = Cast<UItemSlotWidget>(
		UNFGameInstance::GetObjectManager()->CreateWidgetFromName(TEXT("ItemSlotWidget"), GetOwningPlayer()));

	if (!IsValid(dragDisplay))
	{
		//drag display 생성 실패
		FMyDebug::Print(DEBUG_TEXT("Create Drag Display Failed."));
			return;
	}

	////TODO : function으로 줄일 필요가 있음
	dragDisplay->InventoryComponentRef = InventoryComponentRef;
	dragDisplay->InventorySlotNumber = InventorySlotNumber;
	dragDisplay->UpdateSlot();

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
	FMyDebug::Print(DEBUG_TEXT("Item Slot Drop Function"));

	if (!IsValid(InOperation))
	{
		//잘못된 InOperation
		FMyDebug::Print(DEBUG_TEXT("InOperation is Invalid."));
		return false;
	}

	TObjectPtr<UItemSlotWidget> droppedItemSlot = Cast<UItemSlotWidget>(InOperation->Payload);

	if (!IsValid(droppedItemSlot))
	{
		//dropped item slot nullptr
		FMyDebug::Print(DEBUG_TEXT("droppedItemSlot is Invalid."));
		return false;
	}

	int32 dropped_SlotNumber = droppedItemSlot->InventorySlotNumber;
	TObjectPtr<UInventoryComponent> dropped_InventoryComponent = droppedItemSlot->InventoryComponentRef;

	if (IsValid(InventoryComponentRef) && IsValid(dropped_InventoryComponent))
	{
		auto a = InventoryComponentRef->GetInventoryObjectRef();
		auto b = dropped_InventoryComponent->GetInventoryObjectRef();

		bool bSucceed = UInventoryObject::SwapItemBetweenInventory(a, InventorySlotNumber, b, dropped_SlotNumber);

		//TODO?: 현재 인벤토리 갱신은 모든 slot에게서 일어남
		//			필요한 slot만 갱신되도록 하는 방법은?
		return bSucceed;
	}


	FMyDebug::Print(DEBUG_TEXT("Test Fail."));
	return false;
}

void UItemSlotWidget::SetSlotInfo(UInventoryComponent* RefVal, int32 SlotNum)
{
	InventoryComponentRef = RefVal;
	InventorySlotNumber = SlotNum;

	UpdateSlot();
}

void UItemSlotWidget::UpdateSlot()
{
	auto inventoryObj = InventoryComponentRef->GetInventoryObjectRef();

	FItemSlotData itemSlot = *inventoryObj->GetInventoryItem(InventorySlotNumber);

	FItemSheetData itemSheetData =
		UNFGameInstance::GetDataManager()->GetItemData(itemSlot.ItemName);

	if (itemSheetData.Thumbnail == nullptr)
	{
		SlotImage->SetColorAndOpacity(FLinearColor(1, 1, 1, 0.33f));
		SlotImage->SetBrushFromTexture(nullptr);
	}
	else
	{
		SlotImage->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
		SlotImage->SetBrushFromTexture(itemSheetData.Thumbnail);
	}
	

	if (itemSlot.Quantity == 0)
	{
		SlotItemNum->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		SlotItemNum->SetText(FText::FromString(FString::FromInt(itemSlot.Quantity)));
	}
}
