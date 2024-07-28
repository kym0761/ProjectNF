// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Defines/Interfaces/CharacterActionInterfaces.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCharacterState;

/*
*기본 캐릭터
*/
UCLASS()
class PROJECTNF_API ABaseCharacter : public ACharacter , public ICharacterAction
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

#pragma region Component

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	//Farm 작업할 때 LineTrace 위치 지점.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> FarmPos;

#pragma endregion

#pragma region Input

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	//Jump는 기본 ACharacter의 기능을 사용함.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseLeftAction;

	/** movement Function */
	void Move(const FInputActionValue& Value);

	/** look Function */
	void Look(const FInputActionValue& Value);

	/** MouseLeftAction Function */
	void MouseLeft(const FInputActionValue& Value);

#pragma endregion

#pragma region rCharacterState

protected:

	//Character State를 사용하여, 애니메이션이랑 기능을 제어함

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="State", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterState> CharacterState;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/*State 테스트용도, 추후 진짜 기능이 될 수도*/
	void Attack();

	void UseFarmTool();

	void DoWhat();

	void DoPlanting();

public:

	virtual void BattleAction() override;

	virtual void FarmingAction() override;

	virtual void NormalAction() override;

	virtual void PlantingAction() override;

};
