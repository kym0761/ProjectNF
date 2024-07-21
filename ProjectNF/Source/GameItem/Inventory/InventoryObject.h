// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UObject/NoExportTypes.h"
#include "InventoryObject.generated.h"

/**
 * ��ü���� �����ϴ� �κ��丮 ������Ʈ
 * ������ �κ��丮 0~9���� ���ĭ���� ���?
 * ������ �κ��丮 10~??���� ������ �κ��丮�� ���?
 * â��� ��ü������ ū �κ��丮�� ���?
 * 
 * Enemy�� �׳� drop���̺� ���� ����Ͽ� ������ ����� ��?
 */
UCLASS()
class GAMEITEM_API UInventoryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UInventoryObject();

protected:
	//�κ��丮�� �� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlotData> Items;

	//�κ��丮 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 30;

public:

	void InitInventory();

	static bool SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex);

};
