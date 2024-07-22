// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemsChanged);

UCLASS()
class GAMEITEM_API UInventoryObject : public UObject
{
	GENERATED_BODY()
	
public:

	UInventoryObject();

	/*-------------*/
	//�κ��丮 ������ ������ ����Ǹ� �ؾ��� ��
	//1 �κ��丮 UI ������ �����ؾ���.
	//2 �� �̵�? ���� ���� ���� ����� ���� ������ �ҷ����־����?
	//3 ��Ÿ ���
	//���� : �κ��丮 UI ������ �ڿ� ������ ����� �� �κп� bind�� �κ��� ���־���.
	/*-------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	FOnInventoryItemsChanged OnInventoryItemsChanged;

protected:
	//�κ��丮�� �� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlotData> Items;

	//�κ��丮 ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 30;

public:

	void InitInventory();

	//�κ��丮�� �� ������ �ִ���?
	bool HasInventoryEmptySpace() const;
	//�κ��丮�� �������� �� ����� ������ �ִ���?
	bool HasEnoughSpaceForItem(const FItemSlotData& InData) const;
	//Ư�� �������� ������ �ִ���?
	bool HasItemInInventory(const FName& ItemName) const;
	//�κ��丮�� �ִ� Ư�� �������� ������ �������?
	bool HasEnoughQuantityOfItem(const FName& ItemName, const int32 Quantity) const;
	
	//Ư�� ��ġ�� ������ ����
	const FItemSlotData* GetInventoryItem(const int32 Index) const;
	//Index ��ġ�� ������ ���� Set
	bool SetInventoryItem(const int32 Index, const FItemSlotData& InData);
	//�κ��丮�� �������� �ֱ�
	int32 AddItemToInventory(const FItemSlotData& InData);

	//Ư�� ��ġ�� �������� n�� ���� �Լ�
	bool UseItemInInventory(const int32 ItemIndex, const int32 UseQuantity = 1);
	//�κ��丮 ��򰡿� Ư�� �������� n�� ���� �Լ�
	bool UseItemInInventory(const FName& ItemName, const int32 UseQuantity = 1);

	//�κ��丮 ���� Ref
	TArray<FItemSlotData>& GetAllItems();
	//�κ��丮 Size
	int32 GetInventorySize() const;


	static bool SwapItemBetweenInventory(TObjectPtr<UInventoryObject> FromInventory, const int32 FromIndex, TObjectPtr<UInventoryObject> ToInventory, const int32 ToIndex);

};
