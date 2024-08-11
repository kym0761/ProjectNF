// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


class UItemSlotWidget;
class UItemTooltipWidget;
class UGridPanel;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class PROJECTNF_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponentRef;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UGridPanel> InventoryGridPanel;

	UPROPERTY(BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UItemSlotWidget>> ItemSlotWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 ColumnNum = 10;


protected:

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UItemSlotWidget> WeaponSlot;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UItemSlotWidget> ArmorSlot;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UItemSlotWidget> ShieldSlot;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UItemSlotWidget> AccessorySlot01;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UItemSlotWidget> AccessorySlot02;

public:

	virtual void NativeConstruct() override;

	void ToggleInventory();
	void SetInventoryComponentRef(UInventoryComponent* RefVal);

	UFUNCTION()
	void UpdateInventoryUI();
};
