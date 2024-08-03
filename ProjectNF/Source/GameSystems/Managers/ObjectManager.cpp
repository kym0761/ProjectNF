// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"

#include "System/NFGameInstance.h"
#include "ObjectPoolManager.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Blueprint/UserWidget.h"

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

	AActor* actor = nullptr;

	if (toSpawn->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		if (RequestObjectPoolSpawn.IsBound())
		{
			actor = RequestObjectPoolSpawn.Execute(world, toSpawn, Location, Rotation);
		}
		else
		{
			Debug::Print(DEBUG_TEXT("Warning : ObjectPoolManager is Invalid."));
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

UUserWidget* UObjectManager::CreateWidgetFromName(FString ToCreateWidgetName, UObject* WidgetOwner)
{
	auto widgetClass = WidgetBlueprintMap[ToCreateWidgetName];
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

	return widget;
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
		if (RequestObjectPoolDespawn.IsBound())
		{
			RequestObjectPoolDespawn.Execute(DespawnTarget); //ifExecute가 있기는 하지만, Spawn과의 통일성을 위해 그냥 체크 후 Execute한다.
		}
		else
		{
			Debug::Print(DEBUG_TEXT("Warning : ObjectPoolManager is Invalid."));
		}

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
	LoadBlueprints<AActor>(BlueprintMap, AActor::StaticClass(), blueprintPaths, TEXT("BP_")); //ActorBlueprint만 가져온다.

	//UMG
	TArray<FName> widgetBlueprintPaths;
	widgetBlueprintPaths.Add(TEXT("/Game/UI"));
	LoadBlueprints<UUserWidget>(WidgetBlueprintMap, UUserWidget::StaticClass(), widgetBlueprintPaths, TEXT("WBP_"));

}
