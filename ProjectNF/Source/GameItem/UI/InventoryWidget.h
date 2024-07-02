// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryWidget;
class UQuickSlotWidget;

/**
 * 
 */
UCLASS()
class GAMEITEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryWidget> WBP_Inventory;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UQuickSlotWidget> WBP_QuickSlot;

public:

	virtual void NativeConstruct() override;

	void ToggleInventory();
};
