## 목차

1. [ProjectLife](#projectlife)
2. [Inventory System](#inventory-system)
3. [InventoryComponent](#inventorycomponent)
4. [InventoryUI](#inventory-ui)
5. [Drag Drop](#drag-drop)
6. [Shop](#shop)
7. [Crafting](#crafting)
8. [Dungeon Puzzle](#dungeon-puzzle)

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

<img src="ExplainImages/DebugHelper01.png" width="50%">

DebugHelper.h / .cpp는 그런 기능을 만들어 놓은 코드입니다.

__FUNCTION__ 매크로를 기반으로 만든 또다른 매크로로, 언리얼 엔진의 TEXT() 매크로를 개선하고 싶은 디버그 환경에 맞추어 DEBUG_TEXT()와 DEBUG_VATEXT()를 만들었습니다.


<img src="ExplainImages/DebugHelper02.png" width="50%">


또한 간단한 로그 사용을 위한 static 함수를 보유한 클래스를 만들었습니다.

bDebugPlay를 false로 만든다면

일반적으로 사용하는 방법은 다음과 같습니다.

```
FMyDebug::Print(DEBUG_TEXT("abc"));
FMyDebug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *str1, *str2));
```

최초 만들었을 당시에 namespace 단위로 static 함수를 래핑하여 사용했는데, 이렇게 사용했더니 언리얼 엔진 에디터에서는 문제 없었지만

패키징하여 게임 앱으로 만들어 사용했더니 사용이 아예 불가능한 등의 문제가 있어 클래스를 두어 관리하게 됐습니다.







