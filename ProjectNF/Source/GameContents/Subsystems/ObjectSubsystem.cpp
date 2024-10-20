// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "GameContents/GameFarm/FarmlandTile.h"
#include "GameContents/GameItem/Item/ItemPickup.h"
#include "GameContents/Ability/AbilityBase.h"

#include "Defines/Interfaces/ObjectPoolInterfaces.h"

#include "ObjectPoolSubsystem.h"
#include "SheetDataSubsystem.h"
#include "GameInfoSubsystem.h"
#include "InventorySubsystem.h"


UObjectSubsystem::UObjectSubsystem()
{
}

void UObjectSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UObjectSubsystem::Deinitialize()
{
	Super::Deinitialize();

}

void UObjectSubsystem::LoadNiagaras(TMap<FString, TObjectPtr<UNiagaraSystem>>& TargetMap, const TArray<FName>& FolderPaths)
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

		//액터 블루프린트 등은 StaticLoadClass()를 사용하는데,
		//NiagaraSystem은 LoadObject를 사용해야 정상적으로 사용이 가능하다. (패키징 시 문제임.)
		//이 차이 때문에 LoadNiagaras 라는 Function이 따로 필요하다.
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

void UObjectSubsystem::LoadAllBlueprints()
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

	FMyDebug::Print(DEBUG_TEXT("Blueprints Load Successful."));
}

AActor* UObjectSubsystem::Spawn(FString ToSpawnClassName, const FVector& Location, const FRotator& Rotation)
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
		UObjectPoolSubsystem* objectPoolSubsys = world->GetSubsystem<UObjectPoolSubsystem>();
		if (IsValid(objectPoolSubsys))
		{
			actor = objectPoolSubsys->SpawnInPool(world, toSpawn, Location, Rotation);
		}
		else
		{
			FMyDebug::Print(DEBUG_TEXT("objectPoolSubsys is Invalid."));
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

void UObjectSubsystem::BindingActor(AActor* TargetActor)
{
	//GameContents에 있는 액터들의 Delegate를 미리 바인딩하여 의존성을 최대한 낮추는 것을 목표로 만들어진 함수.
	//액터가 무엇인지 확인하고 Cast하여 Delegate에 바인딩한다.

	//각 서브시스템의 기능을 미리 Delegate에 연동하면, 필요할 때마다 서브시스템을 접근하지 않고 기능 사용 가능함.
	//과거엔 GameInstance의 static함수를 만들고 Bind했다. 예시로..-> TBaseStaticDelegateInstance<FItemSheetData(const FName&), FDefaultDelegateUserPolicy>::FFuncPtr
	//를 사용하여 static 함수를 넘길 수도 있긴 한데, 코드가 복잡해질 수 있는 가능성이 있어 변경함.

	if (!IsValid(TargetActor))
	{
		FMyDebug::Print(DEBUG_TEXT("TargetActor Invalid."));
		return;
	}

	if (!IsValid(GWorld))
	{
		FMyDebug::Print(DEBUG_TEXT("GWorld Invalid."));
		return;
	}

	//gameInstance의 서브시스템을 접근하는 것은 딱히 어떤 GameInstance를 사용해도 상관이 없음.
	auto gameinstance = TargetActor->GetWorld()->GetGameInstance();

	auto sheetDataSubsystem = gameinstance->GetSubsystem<USheetDataSubsystem>();
	auto gameInfoSubsystem = gameinstance->GetSubsystem<UGameInfoSubsystem>();
	auto inventorySubsystem = gameinstance->GetSubsystem<UInventorySubsystem>();

	if (TargetActor->IsA(AFarmlandTile::StaticClass()))
	{
		auto farmtile = Cast<AFarmlandTile>(TargetActor);

		if (IsValid(farmtile))
		{
			farmtile->RequestCropSheetData.BindUObject(sheetDataSubsystem, &USheetDataSubsystem::GetCropData);
			farmtile->RequestSpawnItemPickup.BindUObject(this, &UObjectSubsystem::Spawn);
			farmtile->RequestUpdateCropData.BindUObject(gameInfoSubsystem, &UGameInfoSubsystem::UpdateCropInfo);
			farmtile->RequestRemoveCropData.BindUObject(gameInfoSubsystem, &UGameInfoSubsystem::RemoveCropInfo);
		}
	}
	else if (TargetActor->IsA(AItemPickup::StaticClass()))
	{
		auto itemPickup = Cast<AItemPickup>(TargetActor);

		if (IsValid(itemPickup))
		{
			itemPickup->RequestItemData.BindUObject(sheetDataSubsystem ,&USheetDataSubsystem::GetItemData);
			itemPickup->RequestDespawn.BindUObject(this, &UObjectSubsystem::Despawn);
			itemPickup->RequestAddItem.BindUObject(inventorySubsystem , &UInventorySubsystem::AddItemToTargetInventory);
		}
	}
	else if (TargetActor->IsA(AAbilityBase::StaticClass()))
	{
		auto abilityBase = Cast <AAbilityBase>(TargetActor);

		if (IsValid(abilityBase))
		{
			abilityBase->RequestSpawnNiagara.BindUObject(this, &UObjectSubsystem::SpawnNiagaraSystem);
			abilityBase->RequestDespawnAbility.BindUObject(this, &UObjectSubsystem::Despawn);
		}
	}
	else if (IsValid(TargetActor))
	{
		FMyDebug::Print(DEBUG_TEXT("No Needed."));
	}
	else
	{
		FMyDebug::Print(DEBUG_TEXT("Binding Actor Failed."));
	}
}

UUserWidget* UObjectSubsystem::CreateWidgetBlueprint(FString ToCreateWidgetName, APlayerController* WidgetOwner)
{
	//WidgetBP 이름을 알고 있다면, 코드를 통해 언제든 WidgetBlueprint로 만든 UI를 띄울 수 있다.

	TSubclassOf<UUserWidget> widgetClass = WidgetBlueprintMap[ToCreateWidgetName];
	UUserWidget* widget = CreateWidget<UUserWidget>(WidgetOwner, widgetClass);

	return widget;
}

void UObjectSubsystem::Despawn(AActor* DespawnTarget)
{
	if (!IsValid(GEngine))
	{
		FMyDebug::Print(DEBUG_TEXT("No GEngine."));
		return;
	}
	
	UWorld* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	if (!IsValid(world))
	{
		FMyDebug::Print(DEBUG_TEXT("No World."));
		return;
	}

	//Despawn할 Actor가 ObjectPool로 관리되고 있었다면? ObjectPoolSubsystem에게 Despawn을 넘긴다.
	if (DespawnTarget->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		UObjectPoolSubsystem* objectPoolSubsys = world->GetSubsystem<UObjectPoolSubsystem>();
		if (!IsValid(objectPoolSubsys))
		{
			FMyDebug::Print(DEBUG_TEXT("objectPoolSubsys is Invalid."));
		}
		
		objectPoolSubsys->DespawnToPool(DespawnTarget);
	}
	else //ObjectPool에서 관리되지 않는 Actor이므로 그냥 없앤다.
	{
		DespawnTarget->Destroy();
	}
}

UNiagaraComponent* UObjectSubsystem::SpawnNiagaraSystem(FString ToSpawnNiagaraName, const FVector& Location, const FRotator& Rotation)
{
	//Niagara이름만 알고 있다면, 원하는 위치에 이펙트를 Spawn할 수 있음.

	if (!IsValid(GEngine))
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

	//없는 Niagara임
	if (!NiagaraSystemMap.Contains(ToSpawnNiagaraName))
	{
		FMyDebug::Print(DEBUG_VATEXT(TEXT("Invalid Niagara Name. -> %s"), *ToSpawnNiagaraName));
		return nullptr;
	}

	//Niagara는 Actor나 Widget 블루프린트와 다르게
	//TSubclassOf가 아닌, TObjectPtr로 관리됨.
	auto toSpawn = NiagaraSystemMap[ToSpawnNiagaraName];

	return UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, NiagaraSystemMap[ToSpawnNiagaraName], Location, Rotation);
}
