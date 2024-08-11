// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTooltipWidget.h"

#include "System/NFGameInstance.h"
#include "Managers/DataManager.h"
#include "DebugHelper.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemTooltipWidget::SetItemTooltipWidget(FItemSlotData SlotData)
{

	auto itemsheetdata = UNFGameInstance::GetItemData(SlotData.ItemName);

	ItemImage->SetBrushFromTexture(itemsheetdata.Thumbnail);

	FLanguageSheetData langNameData = UNFGameInstance::GetLanguageData(FName(itemsheetdata.ItemNameID.ToString()));
	FLanguageSheetData langDescData = UNFGameInstance::GetLanguageData(FName(itemsheetdata.DescriptionID.ToString()));

	//TODO: GameInstance에서 언어 Enum을 가지고 관리하도록 해야함.
	ELanguage currentLanguage = ELanguage::Korean;

	switch (currentLanguage)
	{
	case ELanguage::Korean:
		ItemNameTextBlock->SetText(langNameData.Kor);
		ItemDescTextBlock->SetText(langDescData.Kor);
		break;
	case ELanguage::English:
		ItemNameTextBlock->SetText(langNameData.Eng);
		ItemDescTextBlock->SetText(langDescData.Eng);
		break;
	default:
		break;
	}

}
