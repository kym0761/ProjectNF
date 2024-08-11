// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Defines/Data.h"
#include "ItemTooltipWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * TooltipWidget은 UUserWidget내에 존재하는 Ref 변수가 있으므로, 연동하여 사용한다.
 */
UCLASS()
class PROJECTNF_API UItemTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> ItemNameTextBlock;

	UPROPERTY(Meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> ItemDescTextBlock;

protected:

	virtual void NativeConstruct() override;


public:

	void SetItemTooltipWidget(FItemSlotData SlotData);

};
