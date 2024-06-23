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

		//ButtonMesh�� õõ�� �Ʒ���?
		ButtonMesh->SetRelativeLocation(lerpVal);
	}
	else
	{
		//ButtonMesh�� õõ�� ����?

		FVector lerpVal = FMath::Lerp(ButtonMesh->GetRelativeLocation(), ButtonUpPos, DeltaTime*10);

		ButtonMesh->SetRelativeLocation(lerpVal);
	}

	if (bTriggerActive)
	{
		TriggerTimer += DeltaTime;
	}

	//��ư�� ��� �ִ� ����, Trigger()�� ��� ȣ���Ͽ� ��ư ���� �ڿ� �ð������� �ִ� PuzzleActor�� �ٽ� Trigger�Ѵ�.
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

	// CharacterMovement Ȥ�� PhysicsComponent.�� ���� ������ ButtonDown��.
	if ((IsValid(characterMovement) 
		|| (primitiveComp && primitiveComp->IsSimulatingPhysics())))
	{
		//Button Down.
		ButtonDown();
	}
}

void APuzzleButton::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//EndOverlap�� ������ ��, ���� ��ư ���� ���𰡰� �ִ����� Ȯ���ؾ��Ѵ�.

	TArray<UPrimitiveComponent*> overlappingComponents;
	GetOverlappingComponents(overlappingComponents);

	//�ϴ� false
	bool temp = false;

	//CharacterMovement Ȥ�� PhysicsComponent�� �ִ����� Ȯ���Ѵ�.
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

		//ĳ���Ͱ� ��� �ְų�, Physic ��ü�� ���� ��ư ���� ���� �� temp�� true�� �����ϰ� �������´�.
		if (IsValid(characterMovement) || (IsValid(i) && i->IsSimulatingPhysics()))
		{
			temp = true;
			break;
		}
	}

	//temp�� false�� buttonUp �õ��Ѵ�.
	if (temp == false)
	{
		ButtonUp();
	}

}

void APuzzleButton::ButtonUp()
{
	//false�̸� buttonUp ����
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
	//true�� buttonDown ����
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

