// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleButton.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APuzzleButton::APuzzleButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(40.0f);
	SetRootComponent(Sphere);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BodyMesh->SetupAttachment(RootComponent);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ButtonMesh->SetupAttachment(BodyMesh);

	ButtonUpPos = FVector(0, 0, 0);
	ButtonDownPos = FVector(0, 0, -10.0f);
	TriggerInterval = 0.25f;

}

void APuzzleButton::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APuzzleButton::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APuzzleButton::OnButtonEndOverlap);
}

void APuzzleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bTriggerActive)
	{
		FVector lerpVal= FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonDownPos, DeltaTime*10);

		//ButtonMesh를 천천히 아래로?
		ButtonMesh->SetRelativeLocation(lerpVal);
	}
	else
	{
		//ButtonMesh를 천천히 위로?

		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonUpPos, DeltaTime*10);

		ButtonMesh->SetRelativeLocation(lerpVal);
	}

	if (bTriggerActive)
	{
		TriggerTimer += DeltaTime;
	}

	//버튼을 밟고 있는 동안, Trigger()를 계속 호출하여 버튼 누른 뒤에 시간제한이 있는 PuzzleActor를 다시 Trigger한다.
	if (bTriggerActive && (TriggerTimer >= TriggerInterval))
	{
		ITriggerable::Execute_Trigger(this);
		//Execute_Trigger();

		TriggerTimer = 0.0f;
	}

}

void APuzzleButton::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCharacterMovementComponent* characterMovement = OtherActor->FindComponentByClass<UCharacterMovementComponent>();
	UPrimitiveComponent* primitiveComp = OtherComp;

	// CharacterMovement 혹은 PhysicsComponent.가 위에 있으면 ButtonDown함.
	if ((IsValid(characterMovement) 
		|| (primitiveComp && primitiveComp->IsSimulatingPhysics())))
	{
		//Button Down.
		ButtonDown();
	}
}

void APuzzleButton::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//EndOverlap이 동작할 때, 아직 버튼 위에 무언가가 있는지를 확인해야한다.

	TArray<UPrimitiveComponent*> overlappingComponents;
	GetOverlappingComponents(overlappingComponents);

	//일단 false
	bool temp = false;

	//CharacterMovement 혹은 PhysicsComponent가 있는지를 확인한다.
	for (UPrimitiveComponent* i : overlappingComponents)
	{
		if (!IsValid(i))
		{
			continue;
		}

		AActor* owner = i->GetOwner();

		if (!IsValid(owner))
		{
			continue;
		}

		UCharacterMovementComponent* characterMovement = owner->FindComponentByClass<UCharacterMovementComponent>();

		//캐릭터가 밟고 있거나, Physic 물체가 아직 버튼 위에 있을 때 temp를 true로 세팅하고 빠져나온다.
		if (IsValid(characterMovement) || (IsValid(i) && i->IsSimulatingPhysics()))
		{
			temp = true;
			break;
		}
	}

	//temp가 false면 buttonUp 시도한다.
	if (temp == false)
	{
		ButtonUp();
	}

}

void APuzzleButton::ButtonUp()
{
	//false이면 buttonUp 무시
	if (bTriggerActive == false)
	{
		return;
	}

	bTriggerActive = false;
	ITriggerable::Execute_Trigger(this);
	//Execute_Trigger();
}

void APuzzleButton::ButtonDown()
{
	//true면 buttonDown 무시
	if (bTriggerActive == true)
	{
		return;
	}

	bTriggerActive = true;
	//Trigger();
	//Execute_Trigger();
	ITriggerable::Execute_Trigger(this);
}

void APuzzleButton::Trigger_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-5, 5.0f, FColor::Black, TEXT("Trigger"));
		UE_LOG(LogTemp, Warning, TEXT("Trigger"));
	}

	for (auto i : TriggerTargets)
	{
		if (i->GetClass()->ImplementsInterface(UBeTriggerable::StaticClass()))
		{
			IBeTriggerable::Execute_BeTriggered(i);
		}
	}

}

