// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
* ����� �ڵ尡 ����ִ��� Ȯ���ϱ� ���� ���� ����� ��ũ��
* �ʿ������ ����� �ڵ带 ��Ȱ��ȭ�ϱ� ������.
* UE_LOG�� AddOnScreenDebugMessage�� �ǵ����̸� �� �ڵ�� ��ü�� ��.
*/

//����) AActor::BeginPlay()
#define FUNCTION_NAME (TEXT(" Function Name : ") + FString(__FUNCTION__)+TEXT(" "))

//����) AActor::Func���� ::Func�� ������ AActor�� ����.
#define CURRENT_CLASS (TEXT(" Class Name : ") + FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) + TEXT(" "))

//�Լ��� ���θ� ����
#define CURRENT_LINE  (TEXT(" Line : ") + FString::FromInt(__LINE__) + TEXT(" "))

//����) void __cdecl AActor::BeginPlay(void) �������� ��µ�.
#define CURRENT_FUNCSIG (TEXT("/ Func signature : ") +FString(__FUNCSIG__)+ TEXT(" "))
#define DEBUG_TEXT_POSITION (TEXT("\n") + FUNCTION_NAME + TEXT("\n") + CURRENT_LINE)

//param0 �� string���� �� ��.   ����) DEBUG_TEXT("abc")
#define DEBUG_TEXT(Param0) (TEXT(Param0)+DEBUG_TEXT_POSITION)

/**
 * 
 */
namespace Debug
{
	//�� ���� false�� �ٲٸ� ��� ������ ����׸� ��Ȱ��ȭ�� �� ����.
	static bool bDebugPlay = true;

	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
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

}