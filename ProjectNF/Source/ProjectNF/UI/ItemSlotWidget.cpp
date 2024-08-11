// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/DragDropOperation.h"
#include "DebugHelper.h"

#include "GameItem/Inventory/InventoryComponent.h"
#include "GameItem/Inventory/InventoryObject.h"

#include "System/NFGameInstance.h"
#include "Managers/ObjectManager.h"
#include "Managers/DataManager.h"

#include "ItemTooltipWidget.h"
#include "Ability/AbilityUseItem.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//생성시 Tooltip 위젯을 생성 및 설정한다.
	//아직 사용하지 않으므로 캐스트할 필요 없음.
	auto itemTooltip =
		UNFGameInstance::CreateWidgetFromName(TEXT("ItemTooltip"), GetOwningPlayer());

	SetToolTip(itemTooltip);

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


	//TODO : 정상적인 클릭이라면 아이템 사용 요청
	UseItem();


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

	FItemSlotData itemSlotData = *InventoryComponentRef->GetInventoryObjectRef()->GetInventoryItem(InventorySlotNumber);
	if (itemSlotData.IsEmpty())
	{
		//아이템이 존재하지 않는 공간을 굳이 drag할 필요 없음.
		return;
	}

	////drag display
	TObjectPtr<UItemSlotWidget> dragDisplay = Cast<UItemSlotWidget>(
		UNFGameInstance::CreateWidgetFromName(TEXT("ItemSlotWidget"), GetOwningPlayer()));

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

bool UItemSlotWidget::UseItem()
{
	auto inventoryObj = InventoryComponentRef->GetInventoryObjectRef();

	FItemSlotData itemSlot = *inventoryObj->GetInventoryItem(InventorySlotNumber);

	FItemSheetData itemSheetData = UNFGameInstance::GetItemData(itemSlot.ItemName);

	EItemGroupType itemGroupType = itemSheetData.ItemGroupType;

	switch (itemGroupType)
	{
	case EItemGroupType::None:
		//아무것도 안함
		break;
	case EItemGroupType::Equipment:
		//장착함.
		//아이템 장비 속성에 맞춰서 해당 슬롯과 아이템 자리를 Swap한다.
		{}
		break;
	case EItemGroupType::Consumable:
		//실제 아이템을 사용해야함.
		{
		auto useitemAbility = Cast<AAbilityUseItem>(
			UNFGameInstance::Spawn(TEXT("AbilityUseItem"), GetOwningPlayerPawn()->GetActorLocation()));
		if (IsValid(useitemAbility))
		{
			useitemAbility->InitAbility(GetOwningPlayerPawn(), UNFGameInstance::GetAbilityData(itemSlot.ItemName), GetOwningPlayerPawn());
		}
			return true;
		}
		break;
	default:
		break;
	}

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

	FItemSheetData itemSheetData = UNFGameInstance::GetItemData(itemSlot.ItemName);

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

	//tooltipWidget을 아이템 정보에 맞게 수정한다.
	UItemTooltipWidget* itemTooltip = Cast<UItemTooltipWidget>(GetToolTip());

	if (IsValid(itemTooltip))
	{
		if (itemSheetData.IsEmpty())
		{
			itemTooltip->SetVisibility(ESlateVisibility::Hidden); //빈 아이템 정보는 보여주지 않는다.
		}
		else
		{
			itemTooltip->SetVisibility(ESlateVisibility::HitTestInvisible);// 아이템 정보가 유효하면 보여주어야함.
			itemTooltip->SetItemTooltipWidget(itemSlot);
		}
	}


}
