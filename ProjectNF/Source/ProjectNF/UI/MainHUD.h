// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 메인 UI임.
 * 사용할 UI들은 전부 MainHUD의 위젯으로 관리함
 */
UCLASS()
class PROJECTNF_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
};
