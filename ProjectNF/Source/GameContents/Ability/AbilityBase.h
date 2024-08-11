// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Defines/Data.h"
#include "GameFramework/Actor.h"
#include "Defines/Interfaces/ObjectPoolInterfaces.h"
#include "AbilityBase.generated.h"

class UNiagaraComponent;

DECLARE_DELEGATE_RetVal_ThreeParams(UNiagaraComponent*, FRequestSpawnNiagara, FString, const FVector&, const FRotator&);

DECLARE_DELEGATE_OneParam(FRequestDespawnAbility, AActor*);

UCLASS()
class GAMECONTENTS_API AAbilityBase : public AActor, public IObjectPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityBase();

	//Niagara Spawn을 하는 Delegate
	FRequestSpawnNiagara RequestSpawnNiagara;

	FRequestDespawnAbility RequestDespawnAbility;

protected:

	//어빌리티 사용자
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
	AActor* AbilityOwner;

	//어빌리티 타겟 -> 이 어빌리티에 의해 데미지를 받을 상대
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
	AActor* AbilityTarget;

	UPROPERTY()
	FTimerHandle AbilityDoingTimer;

	////원하는 이펙트의 이름을 입력하면 이펙트가 동작한다. (NS_는 뺀다.)
	//UPROPERTY(EditDefaultsOnly, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
	//FString EffectName;

	UPROPERTY()
	FAbilitySheetData AbilityData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	/*어빌리티는 아래의 기능을 Override하여 구현하도록 한다.*/

	//어빌리티의 Owner를 세팅
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) //블루프린트 테스트 용도 -> 필요없어지면 삭제할 것.
		void InitAbility(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal = nullptr);
	virtual void InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal = nullptr);


	//어빌리티 시작하기
	UFUNCTION(BlueprintNativeEvent)
	void StartAbility();
	virtual void StartAbility_Implementation();
	
	UFUNCTION(BlueprintNativeEvent)
	void DoingAbility();
	virtual void DoingAbility_Implementation();

	//어빌리티 끝마치기
	UFUNCTION(BlueprintNativeEvent)
	void EndAbility();
	virtual void EndAbility_Implementation();

	//void SetAbilityOwner(AActor* OwnerVal);
	//void SetAbilityTarget(AActor* TargetVal);


};
