// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "System/NFGameInstance.h"
#include "ObjectPoolManager.h"

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

		TSubclassOf<AActor> toSpawn = BlueprintMap[ToSpawnClassName];

		auto objPoolManager = UNFGameInstance::GetObjectPoolManager();
		if (!IsValid(objPoolManager))
		{
			Debug::Print(DEBUG_TEXT("Warning : ObjectPoolManager is Invalid."));
		}

		AActor* actor = nullptr;

		if (toSpawn.Get()->ImplementsInterface(UObjectPoolable::StaticClass()))
		{
			if (IsValid(objPoolManager))
			{
				actor = objPoolManager->SpawnInPool(world, toSpawn, Location, Rotation);
			}
		}
		else
		{
			FActorSpawnParameters spawnPram;
			spawnPram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			actor = world->SpawnActor<AActor>(BlueprintMap[ToSpawnClassName], Location, Rotation, spawnPram);
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
	//?
}
