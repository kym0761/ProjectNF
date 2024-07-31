// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "System/NFGameInstance.h"
#include "ObjectPoolManager.h"

#include "AssetRegistry/AssetRegistryModule.h"

UObjectManager::UObjectManager()
{
}

AActor* UObjectManager::Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation)
{
	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("No GEngine."));
		return nullptr;
	}

	UWorld* world = GEngine->GetCurrentPlayWorld();
	if (!IsValid(world))
	{
		Debug::Print(DEBUG_TEXT("No World."));
		return nullptr;
	}

	if (!BlueprintMap.Contains(ToSpawnClassName))
	{
		Debug::Print(DEBUG_TEXT("No Valid Blueprint Name."));
		return nullptr;
	}


	auto toSpawn = BlueprintMap[ToSpawnClassName];

	auto objPoolManager = UNFGameInstance::GetObjectPoolManager();
	if (!IsValid(objPoolManager))
	{
		Debug::Print(DEBUG_TEXT("Warning : ObjectPoolManager is Invalid."));
	}

	AActor* actor = nullptr;

	if (toSpawn->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		if (IsValid(objPoolManager))
		{
			actor = objPoolManager->SpawnInPool(world, toSpawn, Location, Rotation);
		}
	}
	else
	{
		//충돌을 무시하고 무조건 spawn함
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		actor = world->SpawnActor<AActor>(toSpawn, Location, Rotation, spawnParam);
	}

	return actor;
}

void UObjectManager::Despawn(AActor* DespawnTarget)
{
	if (!GEngine)
	{
		Debug::Print(DEBUG_TEXT("No GEngine."));
		return;
	}

	UWorld* world = GEngine->GetCurrentPlayWorld();
	if (!IsValid(world))
	{
		Debug::Print(DEBUG_TEXT("No World."));
		return;
	}

	if (DespawnTarget->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		auto objPoolManager = UNFGameInstance::GetObjectPoolManager();
		if (!IsValid(objPoolManager))
		{
			Debug::Print(DEBUG_TEXT("Warning : ObjectPoolManager is Invalid."));
		}

		objPoolManager->DespawnToPool(DespawnTarget);
	}
	else
	{
		DespawnTarget->Destroy();
	}

}

void UObjectManager::InitManager()
{

	//Blueprints 폴더에 있는 모든 액터 블루프린트를 긁어온다.
	TArray<FName> blueprintPaths;
	blueprintPaths.Add(TEXT("/Game/Blueprints")); //블루프린트를 긁어올 때 폴더 여러개로 분류했다면, 해당 폴더들 전부를 add하면 된다.
	LoadBlueprints(BlueprintMap, AActor::StaticClass(), blueprintPaths); //ActorBlueprint만 가져온다.

}

void UObjectManager::LoadBlueprints(TMap<FString, UClass*>& TargetMap, UClass* TargetClass, const TArray<FName>& FolderPaths)
{
	FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TargetMap.Empty();

	TArray<FAssetData> assetData;

	FARFilter filter;
	filter.bRecursivePaths = true; //폴더 recursive 옵션

	filter.PackagePaths = FolderPaths;

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
			name.RemoveFromStart(TEXT("BP_"));
			BlueprintMap.Add(name, findClass);
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
