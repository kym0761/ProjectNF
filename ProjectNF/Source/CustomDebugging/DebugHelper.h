// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
* 디버깅 코드가 어디있는지 확인하기 위해 만든 디버깅 매크로
* 필요없어진 디버깅 코드를 비활성화하기 유용함.
* UE_LOG와 AddOnScreenDebugMessage를 되도록이면 이 코드로 교체할 것.
*/

//예시) AActor::BeginPlay()
#define FUNCTION_NAME (TEXT(" Function Name : ") + FString(__FUNCTION__)+TEXT(" "))

//예시) AActor::Func에서 ::Func이 빠져서 AActor만 나옴.
#define CURRENT_CLASS (TEXT(" Class Name : ") + FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) + TEXT(" "))

//함수의 라인만 나옴
#define CURRENT_LINE  (TEXT(" Line : ") + FString::FromInt(__LINE__) + TEXT(" "))

//예시) void __cdecl AActor::BeginPlay(void) 형식으로 출력됨.
#define CURRENT_FUNCSIG (TEXT("/ Func signature : ") +FString(__FUNCSIG__)+ TEXT(" "))
#define DEBUG_TEXT_POSITION (TEXT("\n") + FUNCTION_NAME + TEXT("\n") + CURRENT_LINE)

//param0 꼭 TEXT(string)으로 할 것.   예시) DEBUG_TEXT("abc")
#define DEBUG_TEXT(Param0) (TEXT(Param0)+DEBUG_TEXT_POSITION)

//param0을 FString으로 만들어 사용할 것. 예시) FString("abc"); FString::Printf(TEXT("?? : %d"),intVal);
#define DEBUG_STRING(Param0) (Param0 + DEBUG_TEXT_POSITION)
/**
 * 
 */
namespace Debug
{
	//이 값을 false로 바꾸면 모든 파일의 디버그를 비활성화할 수 있음.
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