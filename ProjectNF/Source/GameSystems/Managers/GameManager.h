// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/Interfaces/ManagerInterfaces.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMESYSTEMS_API UGameManager : public UObject, public IManageable
{
	GENERATED_BODY()
	
public:

	UGameManager();

protected:

	/*게임 관련 재화들*/
	UPROPERTY()
	int32 Money;

public:

	int32 GetMoney() const;
	void AddMoney(int32 InMoney);
	bool SpendMoney(int32 Pay);

public:

	virtual void InitManager() override;
};
