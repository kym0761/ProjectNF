// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "InventoryObject.h"

UInventoryManager::UInventoryManager()
{
}

TObjectPtr<UInventoryObject> UInventoryManager::GetInventory(FString InventoryOwner)
{
	if (InventoryOwner.IsEmpty())
	{
		//�߸��� �κ��丮 ���ٹ�
		return nullptr;
	}

	//TODO : �κ��丮 Owner ��ü�� �����ϴ�������..
	if (!InventoryMap.Contains(InventoryOwner))
	{
		//TODO : �κ��丮 ������, ������ ũ�� ������ �ʱ�ȭ? 
		UInventoryObject* inventory = NewObject<UInventoryObject>(this);
		inventory->InitInventory();

		InventoryMap[InventoryOwner] = inventory;
	}


	return InventoryMap[InventoryOwner];
}

void UInventoryManager::ManagerInit()
{
	//?
}
