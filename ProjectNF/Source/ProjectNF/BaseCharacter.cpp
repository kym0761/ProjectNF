// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "DebugHelper.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "CharacterStrategy/ChBattleState.h"
#include "CharacterStrategy/ChFarmingState.h"
#include "CharacterStrategy/ChNormalState.h"
#include "CharacterStrategy/chPlantingState.h"

#include "FarmActors/FarmlandTile.h"

#include "Defines/Data.h"
#include "Managers/GridManager.h"
#include "Managers/ObjectPoolManager.h"
#include "Managers/DataManager.h"

#include "System/NFGameInstance.h"

#include "BaseAnimInstance.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라만 회전시킨다. 캐릭터는 이동할때만 회전한다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//기본 이동 세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1024.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.15f;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 750.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Camera does not rotate relative to arm
	FollowCamera->bUsePawnControlRotation = false;

	FarmPos = CreateDefaultSubobject<USceneComponent>(TEXT("FarmPos"));
	FarmPos->SetupAttachment(GetRootComponent());
	FarmPos->SetRelativeLocation(FVector(100.0f,0.0f,50.0f));

	{
		auto battleState = CreateDefaultSubobject<UChBattleState>(TEXT("BATTLESTATE"));
		auto farmingState = CreateDefaultSubobject<UChFarmingState>(TEXT("FARMINGSTATE"));
		auto normalState = CreateDefaultSubobject<UChNormalState>(TEXT("NORMALSTATE"));

		auto plantingState = CreateDefaultSubobject<UchPlantingState>(TEXT("PlantingSTATE"));

		CharacterStateMap.Add(FString("Battle"), battleState);
		CharacterStateMap.Add(FString("Farming"), farmingState);
		CharacterStateMap.Add(FString("Normal"), normalState);
		CharacterStateMap.Add(FString("Planting"), plantingState);

		CurrentCharacterState = CharacterStateMap[FString("Normal")];

		//!! 블루프린트에서 사용함.
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::MouseLeft(const FInputActionValue& Value)
{
	if (!IsValid(CurrentCharacterState))
	{
		return;
	}

	CurrentCharacterState->StateAction();


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

		EnhancedInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Started, this, &ABaseCharacter::MouseLeft);
	}

}

void ABaseCharacter::Attack()
{
	//근접 공격?

	Debug::Print(DEBUG_TEXT("Attack"));

	auto animInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	if (!IsValid(animInstance))
	{
		Debug::Print(DEBUG_TEXT("AnimInstance Invalid."));
		return;
	}

	animInstance->PlayAttackMontage();

}

void ABaseCharacter::UseFarmTool()
{
	//일단, 지금 farmtool은 땅을 경작하는 기능을 하는걸로 한다.
	//명칭 UseHoe로 변경해야할 듯

	if (!IsValid(FarmlandTile_BP))
	{
		//farmlandtile bp not set

		Debug::Print(DEBUG_TEXT("FarmlandTile BP is not set"));
		return;
	}

	FHitResult hit;

	//farmPos에서 아래로 2000 내려가는 지점으로 trace
	FVector start = FarmPos->GetComponentLocation();
	FVector end = start + FVector::DownVector * 2000.0f;

	//일단 WorldStatic이면 farmTile을 설치한다.
	//추후에 땅의 Physical Material? 을 통해 흙부분에서만 Farmtile을 설치하게 만들 수도 있음.
	bool traceResult
		= GetWorld()->LineTraceSingleByChannel(
			hit,
			start,
			end,
			ECollisionChannel::ECC_WorldStatic);

	if (!traceResult)
	{
		//trace failed
		Debug::Print(DEBUG_TEXT("trace failed"));		
		return;
	}

	UGridManager* gridManager = UNFGameInstance::GetGridManager();
	if (!IsValid(gridManager))
	{
		//gridmanager nullptr
		Debug::Print(DEBUG_TEXT("gridManager nullptr"));
		return;
	}

	FGrid grid = gridManager->WorldToGrid(hit.Location);

	bool bExistOnGrid = gridManager->IsSomethingExistOnGrid(grid);
	if (bExistOnGrid)
	{
		//누가 점유중이라 못함
		Debug::Print(DEBUG_TEXT("already occupying"));
		return;
	}

	FActorSpawnParameters spawnPram;
	spawnPram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto farmtile = GetWorld()->SpawnActor<AFarmlandTile>(
		FarmlandTile_BP, gridManager->GridToWorld(grid), FRotator::ZeroRotator, spawnPram);

	auto gameInstance = Cast<UNFGameInstance>(GetGameInstance());
	if (!IsValid(gameInstance))
	{
		Debug::Print(DEBUG_TEXT("game instance is Invalid."));
	}


	auto dataManager = UNFGameInstance::GetDataManager();
	if (!IsValid(dataManager))
	{
		Debug::Print(DEBUG_TEXT("Data Manager is Invalid."));
	}

	//farmtile에 CropData와 Spawn을 요청하는 기능을 bind해야한다.
	farmtile->OnRequestCropSheetData.BindDynamic(dataManager, &UDataManager::GetCropDataFromSheet);

	auto objectPoolManager = gameInstance->GetObjectPoolManager();
	if (!IsValid(objectPoolManager))
	{
		Debug::Print(DEBUG_TEXT("Object pool Manager is Invalid."));
	}

	farmtile->OnRequestSpawnItemPickup.BindDynamic(objectPoolManager, &UObjectPoolManager::SpawnInPool);
}

void ABaseCharacter::DoWhat()
{
	//뭐할지 안정해짐

	Debug::Print(DEBUG_TEXT("DoWhat"));

}

void ABaseCharacter::DoPlanting()
{


	FHitResult hit;

	//farmPos에서 아래로 2000 내려가는 지점으로 trace
	FVector start = FarmPos->GetComponentLocation();
	FVector end = start + FVector::DownVector * 2000.0f;

	//일단 WorldStatic이면 farmTile을 설치한다.
	//추후에 땅의 Physical Material? 을 통해 흙부분에서만 Farmtile을 설치하게 만들 수도 있음.
	bool traceResult
		= GetWorld()->LineTraceSingleByChannel(
			hit,
			start,
			end,
			ECollisionChannel::ECC_WorldStatic);

	if (!traceResult)
	{
		//trace failed
		Debug::Print(DEBUG_TEXT("trace failed"));
		return;
	}

	UGridManager* gridManager = UNFGameInstance::GetGridManager();
	if (!IsValid(gridManager))
	{
		//gridmanager nullptr
		Debug::Print(DEBUG_TEXT("gridManager nullptr"));
		return;
	}

	FGrid grid = gridManager->WorldToGrid(hit.Location);

	auto farmtile = Cast<AFarmlandTile>(hit.GetActor());

	if (IsValid(farmtile))
	{
		//farmtile의 정보를 set해준다.

		auto cropData = FCropData();
		cropData.bWatered = false;
		cropData.CropName = "Crop01";
		cropData.CurrentGrowth = 0;

		farmtile->SetInfo(cropData);

		Debug::Print(DEBUG_TEXT("Crop Planting OK"));
	}

}

