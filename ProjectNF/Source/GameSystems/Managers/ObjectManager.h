// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "DebugHelper.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ObjectManager.generated.h"

//DECLARE_DYNAMIC_DELEGATE_RetVal_FourParams(AActor*, FRequestObjectPoolSpawn, UObject*, WorldContext, UClass*, PoolableClass, const FVector&, Location, const FRotator&, Rotation);
//DECLARE_DYNAMIC_DELEGATE_OneParam(FRequestObjectPoolDespawn, AActor*, PoolableActor);

DECLARE_DELEGATE_RetVal_FourParams(AActor*, FRequestObjectPoolSpawn, UObject*, UClass*, const FVector&, const FRotator&);
DECLARE_DELEGATE_OneParam(FRequestObjectPoolDespawn, AActor*);


class UNiagaraSystem;
class UNiagaraComponent;
/**
 * ObjectSpawnFactory다.
 */
UCLASS(BlueprintType, Blueprintable)
class GAMESYSTEMS_API UObjectManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UObjectManager();
	
	/*ObjectPoolManager와 연동하여 ObjectPool가능한 액터들을 Spawn & Despawn할 때 사용한다.*/
	FRequestObjectPoolSpawn RequestObjectPoolSpawn;
	FRequestObjectPoolDespawn RequestObjectPoolDespawn;

#pragma region BlueprintsLoad

protected:

	/*
	* BP_ObjectManager에서 등록해 사용한다.
	* Key : "ClassName" ,Value : BP_SomeActor
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TSubclassOf<AActor>> BlueprintMap;

	//Widget Blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TSubclassOf<UUserWidget>> WidgetBlueprintMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TObjectPtr<UNiagaraSystem>> NiagaraSystemMap;

public:

	//특정 폴더안에 있는 Blueprint들을 전부 끌어와 Map으로 만들어 리소스 관리
	//사용법 : LoadBlueprints<AActor>(ActorMap, AActor::StaticClass(), folderPathArray(ex: /Game/PathName), TEXT("BP_"));
	template<typename T>
	void LoadBlueprints(TMap<FString, TSubclassOf<T>>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths, const FString& PrefixToRemove);

	//나이아가라는 TSubclassOf<>가 아니라서 따로 만듬.
	void LoadNiagaras(TMap<FString, TObjectPtr<UNiagaraSystem>>& TargetMap, const TArray<FName>& FolderPaths);

#pragma endregion

public:
	/*
	* Spawn할 때 TSubclassOf<AActor>를 거치지 않고 String으로 Spawn한다.
	* 예시)Spawn(TEXT("WantToSpawn"),Location,Rotation);
	*/
	UFUNCTION()
	AActor* Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	void BindingActor(AActor* TargetActor);

	//UMG를 생성
	UFUNCTION()
	UUserWidget* CreateWidgetFromName(FString ToCreateWidgetName, APlayerController* WidgetOwner);

	void Despawn(AActor* DespawnTarget);

	virtual void InitManager() override;


	UNiagaraComponent* SpawnNiagaraSystem(FString ToSpawnNiagaraName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);



};

#pragma region BlueprintsLoad

template<typename T>
void UObjectManager::LoadBlueprints(TMap<FString, TSubclassOf<T>>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths, const FString& PrefixToRemove)
{
	FMyDebug::Print(DEBUG_VATEXT(TEXT("loading path : %s"), *FolderPaths[0].ToString()));

	FAssetRegistryModule& assetRegistryModule 
		= FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TargetMap.Empty();

	TArray<FAssetData> assetData;

	FARFilter filter; //5.4부터인가 클래스 필터 처리가 사라짐 ㅡ,ㅡ;

	filter.bRecursivePaths = true; //폴더 recursive 옵션
	filter.PackagePaths = FolderPaths; //긁을 target이 되는 폴더

	assetRegistryModule.Get().GetAssets(filter, assetData);

	for (auto asset : assetData)
	{
		if (!IsValid(asset.GetAsset()))
		{
			FMyDebug::Print(DEBUG_TEXT("GetAsset() is Invalid."));
			continue;
		}

		FString name = asset.GetAsset()->GetName();
		FString path = asset.GetObjectPathString(); // /Game/Blueprint/BP_~~

		//FMyDebug::Print(DEBUG_VATEXT(TEXT("asset path : %s"), *path));

#if WITH_EDITOR
		//실제 빌드된 패키지에서는 _C가 자동으로 붙기 때문에 이 기능은 에디터에서만 동작해야한다.
		path = path + TEXT("_C"); //BP인식을 하려면 _C 붙여야함.
#endif

		UClass* findClass = StaticLoadClass(TargetClass,nullptr, *path);

		if (!IsValid(findClass))
		{
			//FMyDebug::Print(DEBUG_TEXT("failed to get findclass"));
			continue;
		}
		else if(!findClass->IsChildOf(TargetClass))
		{
			//FMyDebug::Print(DEBUG_TEXT("findclass is !! Not !! child of TargetClass"));
			continue;
		}

		//찾은 클래스가 Target Class인지 확인

			//BP_ 빼고 key로 만들어 Map에 넣음.
		name.RemoveFromStart(PrefixToRemove);

		//빌드된 패키지에서는 블루프린트 이름에 _C가 자동으로 붙는다.
		name.RemoveFromEnd(TEXT("_C"));

		if (TargetMap.Contains(name))
		{
			//같은 이름의 블루프린트가 있었으므로, 해당 BP_의 이름을 바꾸어야함.
			FMyDebug::Print(DEBUG_VATEXT(TEXT("Warning! --- Same Name NS : %s"), *name));
		}

		TargetMap.Add(name, findClass);

		//FMyDebug::Print(DEBUG_VATEXT(TEXT("key : %s / Val : %s"), *name, *findClass->GetName()));

	}

	//// 제대로 읽었는지 확인.
	//for (auto& i : TargetMap)
	//{
	//	if (IsValid(i.Value))
	//	{
	//		FMyDebug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *i.Key, *i.Value->GetName()));
	//	}
	//	else
	//	{
	//		FMyDebug::Print(DEBUG_VATEXT(TEXT("%s , nullptr"), *i.Key));
	//	}
	//}

	//FMyDebug::Print(TEXT("=============Load Blueprints END============="));
	//FMyDebug::Print(TEXT("============================================="));
}

#pragma endregion
