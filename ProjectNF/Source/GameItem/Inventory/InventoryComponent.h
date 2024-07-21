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
	//인벤토리 아이템 정보가 변경되면 해야할 일
	//1 인벤토리 UI 정보를 변경해야함.
	//2 맵 이동? 게임 저장 등을 고려해 정보 저장을 불러와주어야함?
	//3 기타 등등
	//주의 : 인벤토리 UI 삭제된 뒤에 문제가 생기면 이 부분에 bind된 부분을 없애야함.
	/*-------------*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	FOnInventoryItemsChanged OnInventoryItemsChanged;

protected:

	//인벤토리에 들어간 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	TArray<FItemSlotData> Items;

	//인벤토리 사이즈
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	int32 InventorySize;

	//마우스로 아이템을 나누거나 할 때 사용할 수 있는 임시 공간
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
