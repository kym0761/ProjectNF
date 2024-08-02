// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryObject;

/*
* 실제 인벤토리는 GameInstance
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTNF_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	//인벤토리 생성 및 접근을 위한 ID
	//1) 캐릭터는 캐릭터 이름을 ID로 한다
	//2) 아이템 창고는 설치할 때 ItemNumberID를 ID로 한다..?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString InventoryID;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:

	///*-------------*/
	////인벤토리 아이템 정보가 변경되면 해야할 일
	////1 인벤토리 UI 정보를 변경해야함.
	////2 맵 이동? 게임 저장 등을 고려해 정보 저장을 불러와주어야함?
	////3 기타 등등
	////주의 : 인벤토리 UI 삭제된 뒤에 문제가 생기면 이 부분에 bind된 부분을 없애야함.
	///*-------------*/
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//FOnInventoryItemsChanged OnInventoryItemsChanged;

protected:

	//실제 Inventory Ref
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	UInventoryObject* InventoryObjectRef;

	//마우스로 아이템을 나누거나 할 때 사용할 수 있는 임시 공간
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
	FItemSlotData DraggedItem;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void InitInventoryComponent();

	UInventoryObject* GetInventoryObjectRef();


};
