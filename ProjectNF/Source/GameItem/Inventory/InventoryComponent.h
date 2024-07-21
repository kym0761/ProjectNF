// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemsChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEITEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:

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
	int32 InventorySize;

	//���콺�� �������� �����ų� �� �� ����� �� �ִ� �ӽ� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	FItemSlotData DraggedItem;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	bool CheckInventoryHasSpace() const;
	const FItemSlotData* GetInventoryItem(const int32 Index) const;
	bool SetInventoryItem(const int32 Index, const FItemSlotData& InData);

	int32 AddItemToInventory(const FItemSlotData& InData);
	bool UseItemInInventory(const int32 ItemIndex);
	bool UseItemsInInventory(const FName& ItemName, const int32 Quantity);
	bool CheckItemInInventory(const FName& ItemName) const;
	bool CheckItemWithQuantityInInventory(const FName& ItemName, const int32 Quantity) const;
	int32 GetItemQuantity(const FName& ItemName) const;

	TArray<FItemSlotData> GetAllItems() const;

	void SetInventorySize(const int32 Val);
	int32 GetInventorySize() const;

	void ExpandInventory(const int32 ExpandSize);

	static bool SwapItemBetweenInventory(TObjectPtr<UInventoryComponent> From, const int32 FromSlotIndex, TObjectPtr<UInventoryComponent> To, const int32 ToSlotIndex);

protected:

	void InitializeInventory();
};
