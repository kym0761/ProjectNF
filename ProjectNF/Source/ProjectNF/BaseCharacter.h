// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UBaseCharacterState;

/*
*�⺻ ĳ����
*/
UCLASS()
class PROJECTNF_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();


#pragma region Component

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

#pragma endregion

#pragma region Input

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	//Jump�� �⺻ ACharacter�� ����� �����.
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

protected:

	//Character State�� ����Ͽ�, �ִϸ��̼��̶� ����� ������

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TObjectPtr<UBaseCharacterState>> CharacterStateMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="State", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseCharacterState> CurrentCharacterState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
