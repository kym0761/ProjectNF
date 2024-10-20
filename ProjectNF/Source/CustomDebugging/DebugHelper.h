// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
* 디버깅 코드가 어디있는지 확인하기 위해 만든 디버깅 매크로
* 필요없어진 디버깅 코드를 비활성화하기 유용함.
* UE_LOG와 AddOnScreenDebugMessage를 되도록이면 이 코드로 교체할 것.
*/

//예시) AActor::BeginPlay()
#define FUNCTION_NAME (TEXT(" Func : ") + FString(__FUNCTION__)+TEXT(" "))

//예시) AActor::Func에서 ::Func이 빠져서 AActor만 나옴.
#define CURRENT_CLASS (TEXT(" Class : ") + FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) + TEXT(" "))

//함수의 라인만 나옴
#define CURRENT_LINE  (TEXT("  Line : ") + FString::FromInt(__LINE__) + TEXT(" "))

//예시) void __cdecl AActor::BeginPlay(void) 형식으로 출력됨.
#define CURRENT_FUNCSIG (TEXT("/ Func signature : ") +FString(__FUNCSIG__)+ TEXT(" "))

//custom Format : 필요할 때 알아서 조립해서 쓸 수 있음.
#define DEBUG_TEXT_POSITION (TEXT("\n") + FUNCTION_NAME + TEXT("\n") + CURRENT_LINE)

#define ENDLINE TEXT("\n----------------------------------------")

//param0 꼭 TEXT(string)으로 할 것.   예시) DEBUG_TEXT("abc")
#define DEBUG_TEXT(Param0) (TEXT(Param0)+DEBUG_TEXT_POSITION + ENDLINE)

//예시) DEBUG_VATEXT(TEXT("%s, %s"),*Str1, *Str2);
#define DEBUG_VATEXT(TextFormat, ...) (FString::Printf(TextFormat,__VA_ARGS__) + DEBUG_TEXT_POSITION + ENDLINE)
/**
 *
 */

class CUSTOMDEBUGGING_API FMyDebug
{
private:

	//빌드하기 전에 디버그를 보고 싶지 않다면 이 변수를 false할 것.
	//코드 상에서는 .cpp 파일의 값을 바꾸어야함.
	static bool bDebugPlay;

public:

	FMyDebug();
	~FMyDebug();

	//예시1) FMyDebug::Print(DEBUG_TEXT("ABC"));
	//예시2) FMyDebug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *str1, *str2));
	static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1);

	//외부 코드에서 bDebugPlay를 바꿀려면 이 코드로 바꿀 것.
	//예시) GameMode에 bool 변수를 따로 만들어 Beginplay()에서 bDebugPlay를 bool 변수 값으로 변경하면
	//에디터 인게임 내에서 디버그가 활성/비활성된다.
	//만든 이유 : true -> false / false -> true 바꿀 때마다 이 값 사용하는 코드를 다시 빌드해야함. 그 상황 방지용도다.
	static void SetBoolDebugPlay(bool Val);

};