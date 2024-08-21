// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleButton.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelper.h"

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

	bButtonActive = false;
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


	if (bButtonActive)
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

	if (bButtonActive)
	{
		TriggerTimer += DeltaTime;
	}

	//버튼을 밟고 있는 동안, Trigger()를 계속 호출하여 버튼 누른 뒤에 시간제한이 있는 PuzzleActor를 다시 Trigger한다.
	if (bButtonActive && (TriggerTimer >= TriggerInterval))
	{
		Trigger();
		TriggerTimer = 0.0f;
	}

}

void APuzzleButton::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO : Interact를 위한 overlap 컴포넌트가 닿으면 Actor를 인식해서 버튼이 밟힌 듯이 움직인다.
	//일단 플레이어에 대한 Overlap을 비활성화하고, 게임 플레이에 필요한 overlap 컴포넌트를 무시하도록 설정할 것.


	UCharacterMovementComponent* characterMovement = OtherActor->FindComponentByClass<UCharacterMovementComponent>();
	UPrimitiveComponent* primitiveComp = OtherComp;

	// CharacterMovement 혹은 PhysicsComponent.가 위에 있으면 ButtonDown함.
	if (//(IsValid(characterMovement) ||
		(IsValid(primitiveComp) && primitiveComp->IsSimulatingPhysics()))
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
		if (IsValid(characterMovement) || i->IsSimulatingPhysics())
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
	if (bButtonActive == false)
	{
		return;
	}

	bButtonActive = false;
	Trigger();//deactivate 알림
}

void APuzzleButton::ButtonDown()
{
	//true면 buttonDown 무시
	if (bButtonActive == true)
	{
		return;
	}

	bButtonActive = true;
	Trigger(); // activate 알림
}

void APuzzleButton::Trigger()
{
	FMyDebug::Print(DEBUG_TEXT("Trigger"));

	for (auto i : TriggerTargets)
	{
		IBeTriggerable* beTriggerable = Cast<IBeTriggerable>(i);

		if (beTriggerable)
		{
			beTriggerable->BeTriggered(this, bButtonActive);
		}
	}

}

