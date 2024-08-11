// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Defines/Data.h"
#include "ItemSlotWidget.generated.h"

class UImage;
class UTextBlock;
class UInventoryComponent;

//struct FItemSlotData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseEnterFunc, FItemSlotData, SlotData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseLeaveFunc);
/**
 * 
 */
UCLASS()
class PROJECTNF_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UImage> SlotImage;

	UPROPERTY(Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> SlotItemNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	int32 InventorySlotNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponentRef;

	////Drag Drop에서 쓸 WidgetBP
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", Meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UItemSlotWidget> ItemSlotBP;

//public:
//	
//	UPROPERTY()
//	FOnMouseEnterFunc OnMouseEnterFunc;
//	
//	UPROPERTY()
//	FOnMouseLeaveFunc OnMouseLeaveFunc;

protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonUp(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void DragFunction(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	bool DropFunction(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	bool UseItem();

public:

	void SetSlotInfo(UInventoryComponent* RefVal, int32 SlotNum);

	void UpdateSlot();


};
