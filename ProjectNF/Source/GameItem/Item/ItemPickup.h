// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "Defines/interfaces/ObjectPoolInterfaces.h"
#include "Defines/interfaces/InteractiveInterfaces.h"
#include "GameFramework/Actor.h"
#include "ItemPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

/*
* pickup 사용 예시
* 1 : 인벤토리 슬롯을 땅에 드래그하여 땅에 떨궜을 때 (혹은 밖에 꺼내기 등)
* 2 : 몬스터가 죽었을 때 템 떨어트리기
* 3 : 밭에서 수확물 채집할 때
*/

UCLASS()
class GAMEITEM_API AItemPickup : public AActor, public IInteractive, public IObjectPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	//Needed For Detection.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item", Meta = (AllowPrivateAccess = true))
	FItemSlotData PickupItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser) override;

};
