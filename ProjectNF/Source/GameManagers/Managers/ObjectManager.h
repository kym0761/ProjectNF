// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "DebugHelper.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ObjectManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_FourParams(AActor*, FRequestObjectPoolSpawn, UObject*, WorldContext, UClass*, PoolableClass, const FVector&, Location, const FRotator&, Rotation);
DECLARE_DYNAMIC_DELEGATE_OneParam(FRequestObjectPoolDespawn, AActor*, PoolableActor);
/**
 * ActorSpawnFactory다.
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEMANAGERS_API UObjectManager : public UObject, public IManageable
{
	GENERATED_BODY()

public:

	UObjectManager();
	
	/*ObjectPoolManager와 연동하여 ObjectPool가능한 액터들을 Spawn & Despawn할 때 사용한다.*/
	UPROPERTY()
	FRequestObjectPoolSpawn RequestObjectPoolSpawn;
	UPROPERTY()
	FRequestObjectPoolDespawn RequestObjectPoolDespawn;
protected:

	/*
	* BP_ObjectManager에서 등록해 사용한다.
	* Key : "ClassName" ,Value : BP_SomeActor
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TSubclassOf<AActor>> BlueprintMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object", Meta = (AllowPrivateAccess = true))
	TMap<FString, TSubclassOf<UUserWidget>> WidgetBlueprintMap;

public:
	/*
	* Spawn할 때 TSubclassOf<AActor>를 거치지 않고 String으로 Spawn한다.
	* 예시)Spawn(TEXT("WantToSpawn"),Location,Rotation);
	*/
	UFUNCTION()
	AActor* Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	UFUNCTION()
	UUserWidget* CreateWidgetFromName(FString ToCreateWidgetName, UObject* WidgetOwner);

	void Despawn(AActor* DespawnTarget);

	virtual void InitManager() override;

	//특정 폴더안에 있는 Blueprint들을 전부 끌어와 Map으로 만들어 리소스 관리
	template<typename T>
	void LoadBlueprints(TMap<FString, TSubclassOf<T>>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths , const FString& PrefixToRemove);

};

template<typename T>
void UObjectManager::LoadBlueprints(TMap<FString, TSubclassOf<T>>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths, const FString& PrefixToRemove)
{
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
		FString name = asset.GetAsset()->GetName();
		FString path = asset.GetObjectPathString();
		path = path + TEXT("_C"); //BP인식을 하려면 _C 붙여야함.

		UClass* findClass = FindObject<UClass>(nullptr, *path);

		//찾은 클래스가 Target Class인지 확인
		if (IsValid(findClass) && findClass->IsChildOf(TargetClass))
		{
			//BP_ 빼고 key로 만들어 Map에 넣음.
			name.RemoveFromStart(PrefixToRemove);
			TargetMap.Add(name, findClass);
		}
	}

	for (auto& i : TargetMap)
	{
		if (IsValid(i.Value))
		{
			Debug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *i.Key, *i.Value->GetName()));
		}
		else
		{
			Debug::Print(DEBUG_VATEXT(TEXT("%s , nullptr"), *i.Key));
		}
	}
}
