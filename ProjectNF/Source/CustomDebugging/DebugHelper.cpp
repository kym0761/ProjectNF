// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugHelper.h"

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
