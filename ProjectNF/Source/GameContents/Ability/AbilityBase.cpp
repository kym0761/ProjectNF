// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "DebugHelper.h"

// Sets default values
AAbilityBase::AAbilityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//어빌리티가 데미지를 받고 파괴되는 것을 막기 위해 일단 사용함.
	SetCanBeDamaged(false);
}

// Called when the game starts or when spawned
void AAbilityBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAbilityBase::InitAbility_Implementation(AActor* AbilityOwnerVal, const FAbilitySheetData AbilityDataVal, AActor* AbilityTargetVal)
{
	//어빌리티 Owner를 Set함.

	if (!IsValid(AbilityOwnerVal))
	{
		FMyDebug::Print(DEBUG_TEXT("Ability Owner Val is Invalid."));
		return;
	}

	AbilityOwner = AbilityOwnerVal;
	AbilityData = AbilityDataVal;

	//!! after DO : 일부 스킬은, InitAbility를 override하여 애니메이션 실행 및 어빌리티 동작을 실행할 수 있도록 해야함.

	//일단 Base는 init하자마자 StartAbility()를 실행하고, 바로 EndAbility()를 동작한다. -> 예시일 뿐이지 절대 이렇게 만들지 말것.
	//EndAbility()에서 Destroy하여 어빌리티가 맵에서 사라짐.

	FMyDebug::Print(DEBUG_TEXT("Ability Init OK."));

	StartAbility();

}

void AAbilityBase::StartAbility_Implementation()
{
	FMyDebug::Print(DEBUG_VATEXT(TEXT(" Start Ability() --- Ability Owner : %s"), *AbilityOwner->GetName()));
	EndAbility();

	//어빌리티 시작하고 여러 케이스가 존재할 수 있음

	//1) 즉발 : 스킬 사용 즉시 데미지를 주고 끝내기
	//2) 지속 : 스킬 사용 후 n초 동안 데미지를 주기
	//3) 무한 : 스킬 사용하면 무한한 시간 동안 능력이 증가
	//4) 복합? : 스킬 사용 즉시 데미지를 주며, 지속시간 동안 능력을 증가 등등
	//5) 다른 효과를 넘김? : 범위기에 닿았을 때, 닿은 적에게 각각 지속적인 데미지를 준다.

	//아이디어
	//1) 즉발 : StartAbility에서 적에게 데미지를 준 뒤 바로 EndAbility를 부른다
	//2) 지속 : StartAbility에서 Timer를 가동하여 지속적으로 데미지를 준다.
	//3) 무한 : Timer가 동작하지만 꺼지지 않게 한다.
	//4) 복합 : StartAbility에서 데미지를 준 뒤, Timer가 동작하게 한다.
	//5) 다른 효과를 넘김 : StartAbility에서 범위 감지를 한 뒤, 적에게 틱뎀을 입히는 어빌리티를 가동하게 만든다. 어빌리티 Owner는 당연히 현재 Ability의 Owner로 세팅함.

}

void AAbilityBase::DoingAbility_Implementation()
{
	//타이머로 동작할 기능은 여기에
	
	//지속시간동안 무언가를 할 것인지?

	//예시 :
	//1) 지속 힐
	//2) 지속 틱뎀
	//3) ...
}

void AAbilityBase::EndAbility_Implementation()
{
	FMyDebug::Print(DEBUG_VATEXT(TEXT(" End Ability() --- Ability Owner : %s"), *AbilityOwner->GetName()));
	Destroy();



	//어빌리티를 끝마칠 때 여러 케이스가 존재할 수 있다.

	//1) 아무일도 안벌어짐
	//2) 끝날때 데미지를 줌
	//3) ...
}

//void AAbilityBase::SetAbilityOwner(AActor* OwnerVal)
//{
//	AbilityOwner = OwnerVal;
//}
//
//void AAbilityBase::SetAbilityTarget(AActor* TargetVal)
//{
//	AbilityTarget = TargetVal;
//}
