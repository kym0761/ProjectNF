// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "Blueprint/UserWidget.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Defines/Interfaces/ObjectPoolInterfaces.h"

#include "System/NFGameInstance.h"

#include "GameContents/GameFarm/FarmlandTile.h"
#include "GameContents/GameItem/Item/ItemPickup.h"
#include "GameContents/Ability/AbilityBase.h"

UObjectManager::UObjectManager()
{
}

void UObjectManager::LoadNiagaras(TMap<FString, TObjectPtr<UNiagaraSystem>>& TargetMap, const TArray<FName>& FolderPaths)
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

		UNiagaraSystem* findClass = LoadObject<UNiagaraSystem>(nullptr, *path);


		//찾은 클래스가 유효한지 확인
		if (IsValid(findClass))
		{
			//NS_ 빼고 key로 만들어 Map에 넣음.
			name.RemoveFromStart(TEXT("NS_"));

			if (TargetMap.Contains(name))
			{
				//같은 이름의 나이아가라가 있었으므로, 해당 NS_의 이름을 바꾸어야함.
				FMyDebug::Print(DEBUG_VATEXT(TEXT("Warning! --- Same Name NS : %s"), *name));
			}

			TargetMap.Add(name, findClass);
		}
	}

	for (auto& i : TargetMap)
	{
		if (IsValid(i.Value))
		{
			FMyDebug::Print(DEBUG_VATEXT(TEXT("%s, %s"), *i.Key, *i.Value->GetName()));
		}
		else
		{
			FMyDebug::Print(DEBUG_VATEXT(TEXT("%s , nullptr"), *i.Key));
		}
	}

}

AActor* UObjectManager::Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation)
{
	if (!GEngine)
	{
		FMyDebug::Print(DEBUG_TEXT("No GEngine."));
		return nullptr;
	}

	UWorld* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	if (!IsValid(world))
	{
		FMyDebug::Print(DEBUG_TEXT("No World."));
		return nullptr;
	}

	if (!BlueprintMap.Contains(ToSpawnClassName))
	{
		FMyDebug::Print(DEBUG_TEXT("No Valid Blueprint Name."));
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
			FMyDebug::Print(DEBUG_TEXT("RequestObjectPoolSpawn is not Bound."));
		}
	}
	else
	{
		//충돌을 무시하고 무조건 spawn함
		FActorSpawnParameters spawnParam;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		actor = world->SpawnActor<AActor>(toSpawn, Location, Rotation, spawnParam);
	}

	BindingActor(actor);

	return actor;
}

void UObjectManager::BindingActor(AActor* TargetActor)
{
	//GameContents에 있는 액터들의 Delegate를 바인딩하여 의존성을 최대한 낮추는 것을 목표로 만들어진 함수.
	//액터가 무엇인지 확인하고 Cast하여 Delegate에 바인딩한다.

	//? : ObjectPool 한 액터에 제대로 동작하는지?

	//예시로.. TBaseStaticDelegateInstance<FItemSheetData(const FName&), FDefaultDelegateUserPolicy>::FFuncPtr
	//를 사용하여 static 함수를 넘길 수도 있긴 한데, 코드가 복잡해질 수 있는 가능성이 있어
	//Object를 Spawn할 때만 GameInstance에 접근하여 static 함수를 바인드하도록 한다.

	if (TargetActor->IsA(AFarmlandTile::StaticClass()))
	{
		auto farmtile= Cast<AFarmlandTile>(TargetActor);

		if (IsValid(farmtile))
		{
			farmtile->RequestCropSheetData.BindStatic(&UNFGameInstance::GetCropData);
			farmtile->RequestSpawnItemPickup.BindStatic(&UNFGameInstance::Spawn);
			farmtile->RequestUpdateCropData.BindStatic(&UNFGameInstance::UpdateCropInfo);
			farmtile->RequestRemoveCropData.BindStatic(&UNFGameInstance::RemoveCropInfo);
		}
	}
	else if (TargetActor->IsA(AItemPickup::StaticClass()))
	{
		auto itemPickup = Cast<AItemPickup>(TargetActor);

		if (IsValid(itemPickup))
		{
			itemPickup->RequestItemData.BindStatic(&UNFGameInstance::GetItemData);
			itemPickup->RequestDespawn.BindStatic(&UNFGameInstance::Despawn);
			itemPickup->RequestAddItem.BindStatic(&UNFGameInstance::AddItemToTargetInventory);
		}
	}
	else if (TargetActor->IsA(AAbilityBase::StaticClass()))
	{
		auto abilityBase = Cast <AAbilityBase>(TargetActor);

		if (IsValid(abilityBase))
		{
			abilityBase->RequestSpawnNiagara.BindStatic(&UNFGameInstance::SpawnNiagaraSystem);
			abilityBase->RequestDespawnAbility.BindStatic(&UNFGameInstance::Despawn);
		}
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("Binding Actor Failed."));
	}


}

UUserWidget* UObjectManager::CreateWidgetFromName(FString ToCreateWidgetName, APlayerController* WidgetOwner)
{
	auto widgetClass = WidgetBlueprintMap[ToCreateWidgetName];
	UUserWidget* widget = CreateWidget<UUserWidget>(WidgetOwner, widgetClass);

	return widget;
}

void UObjectManager::Despawn(AActor* DespawnTarget)
{
	if (!GEngine)
	{
		FMyDebug::Print(DEBUG_TEXT("No GEngine."));
		return;
	}

	UWorld* world = GEngine->GetCurrentPlayWorld();
	if (!IsValid(world))
	{
		FMyDebug::Print(DEBUG_TEXT("No World."));
		return;
	}

	if (DespawnTarget->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		if (RequestObjectPoolDespawn.IsBound())
		{
			RequestObjectPoolDespawn.Execute(DespawnTarget); //void function Delegate라서 ExecuteIfBound()가 있기는 하지만, Spawn과의 통일성을 위해 그냥 체크 후 Execute한다.
		}
		else
		{
			FMyDebug::Print(DEBUG_TEXT("RequestObjectPoolDespawn is not Bound."));
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


	//Niagara
	TArray<FName> niagaraPaths;
	niagaraPaths.Add(TEXT("/Game/Niagaras"));
	LoadNiagaras(NiagaraSystemMap, niagaraPaths);
}

UNiagaraComponent* UObjectManager::SpawnNiagaraSystem(FString ToSpawnNiagaraName, const FVector& Location, const FRotator& Rotation)
{

	if (!GEngine)
	{
		FMyDebug::Print(DEBUG_TEXT("No GEngine."));
		return nullptr;
	}

	UWorld* world = GEngine->GetCurrentPlayWorld();
	
	if (!IsValid(world))
	{
		FMyDebug::Print(DEBUG_TEXT("No World."));
		return nullptr;
	}

	if (!NiagaraSystemMap.Contains(ToSpawnNiagaraName))
	{
		FMyDebug::Print(DEBUG_VATEXT(TEXT("Invalid Niagara Name. -> %s"), *ToSpawnNiagaraName));
		return nullptr;
	}

	auto toSpawn = NiagaraSystemMap[ToSpawnNiagaraName];

	return UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, NiagaraSystemMap[ToSpawnNiagaraName], Location, Rotation);
}
