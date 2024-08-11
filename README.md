## 목차

1. [ProjectNF](#projectnf)
2. [DebugHelper](#debughelper)

5. [Drag Drop](#drag-drop)


# ProjectNF

NF는 New Farm의 줄임말입니다.

이번 프로젝트는 기존에 구현했던 프로젝트의 코드를 리메이크해 개선하면서 프레임워크화 하기 위한 목표로 시작됐습니다.

# DebugHelper

DebugHelper는 디버그 로그를 사용하면서 불편했던 부분을 개선하기 위해 만든 커스텀 로그 기능입니다.

```
UE_LOG();
GEngine->AddOnScreenDebugMessage();
```
언리얼 엔진에서는 위 코드를 사용하여 로그를 남기는데, 프로젝트를 계속 진행하면서 늘어난 코드에 비례해 로그 코드가 늘어나고, 게임을 실행할 때마다 비활성화하지 못한 로그가 계속 보이고 찾기 힘든 문제점을 가지고 있습니다.

때문에 디버그 로그가 나올 때 어느 코드, 어느 지점에서 디버그가 발생하는지 나타날 수 있게 만들고 싶었습니다.

<img src="ExplainImages/DebugHelper01.png" width="100%">

DebugHelper.h / .cpp는 그런 기능을 만들어 놓은 코드입니다.

__FUNCTION__ 매크로를 기반으로 만든 또다른 매크로로, 언리얼 엔진의 TEXT() 매크로를 개선하고 싶은 디버그 환경에 맞추어 DEBUG_TEXT()와 DEBUG_VATEXT()를 만들었습니다.


<img src="ExplainImages/DebugHelper02.png" width="100%">


또한 간단한 로그 사용을 위한 static 함수를 보유한 클래스를 만들었습니다.

bDebugPlay를 false로 만든다면

일반적으로 사용하는 방법은 다음과 같습니다.

```
FMyDebug::Print(DEBUG_TEXT("abc"));
FMyDebug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *str1, *str2));
```

# GameInstance

<img src="ExplainImages/GameInstance01.png" width="100%">

GameInstance는 언리얼 엔진 내에서 레벨이 전환되어도 사라지지 않고 유지되는 객체입니다.

그러므로, GameInstance를 매니저를 모아두는 싱글톤 클래스로서 사용하고 게임 로직과 관련된 Manager들을 전부 GameInstance에서 관리하도록 만듭니다.

# Managers

## DataManager

<img src="ExplainImages/DataManager01.png" width="100%">

DataManager는 게임에서 사용할 스프레드시트 데이터를 보관하고 관리하는 매니저 클래스입니다.


<img src="ExplainImages/DataManager02.png" width="100%">
<img src="ExplainImages/DataManager03.png" width="100%">

언리얼 엔진의 구조체로 DataTable의 시트 구조만든 뒤 DataTable 블루프린트를 만들어 데이터를 관리합니다.

<img src="ExplainImages/DataManager04.png" width="100%">
<img src="ExplainImages/DataManager05.png" width="100%">

DataTable을 BP_DataManager의 배열로 연결한 뒤, 코드 내에서 template 함수로 각 데이터에 맞춰 SheetData를 로드하여 Map에 옮긴 뒤, 필요할 때마다 Map의 Key값에 맞는 SheetData를 얻어낼 수 있습니다.

```
//사용 예시
//Item01에 해당하는 데이터를 얻어온다.
FItemSheetData data = UNFGameInstance::GetItemData(TEXT("Item01"));
```

## GridManager

<img src="ExplainImages/GridManager01.png" width="100%">

월드를 적절한 크기의 값으로 나누어 만들어진 좌표로 매칭하여 그리드 칸에 농작물을 심고 키우는 시스템의 일부입니다.


## InventoryManager

<img src="ExplainImages/InventoryManager01.png" width="100%">


실질적인 인벤토리인 InventoryObject를 관리하는 매니저 클래스입니다.

플레이어의 InventoryComponent에서는 Inventory ID 값이 존재하는데, InventoryID 값으로 매니저의 InventoryObject를 확인하여

존재하지 않으면 새로운 인벤토리를 만들고, 존재하는 InventoryObject가 있다면 접근을 허용합니다.


## ObjectManager

<img src="ExplainImages/ObjectManager01.png" width="100%">

ObjectManager는 Content폴더에 있는 블루프린트로 만들어진 클래스를 전부 게임 시작시 로드하여 사용자가 필요하면 원하는 Key값의 클래스를 Spawn을 도와주는 팩토리 패턴의 매니저 클래스입니다.

<img src="ExplainImages/ObjectManager02.png" width="100%">

ObjectManager는 게임 시작시 각 종류에 맞는 블루프린트 등의 경로에 맞춰 폴더 안에 있는 모든 블루프린트를 매니저에 로드합니다.

로드한 블루프린트는 "BP_라는 접두어를 제거한 이름"을 제거한 문자열을 Key값으로 사용합니다.

```
//사용예시

//BP_TestActor라는 클래스를 Spawn한다.
UNFGameInstance::Spawn(TEXT("TestActor"),Location, Rotation);

``` 

