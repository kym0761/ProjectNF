// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugHelper.h"

//기본값은 true로, 게임 전체의 debug Text를 비활성화하고 싶다면 false로 바꿀 것.
//혹은 SetBoolDebugPlay() 사용할 것
bool FMyDebug::bDebugPlay = true;

void FMyDebug::Print(const FString& Msg, const FColor& Color, int32 InKey)
{

	if (!bDebugPlay)
	{
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(InKey, 3.0f, Color, Msg);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

}

void FMyDebug::SetBoolDebugPlay(bool Val)
{
	bDebugPlay = Val;
}

FMyDebug::FMyDebug()
{
}

FMyDebug::~FMyDebug()
{
}
