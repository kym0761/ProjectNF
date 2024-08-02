// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

UGameManager::UGameManager()
{
	Money = 1234;
}

int32 UGameManager::GetMoney() const
{
	return Money;
}

void UGameManager::AddMoney(int32 InMoney)
{
	Money += InMoney;
}

bool UGameManager::SpendMoney(int32 Pay)
{
	if (Pay > Money)
	{
		return false;
	}

	Money -= Pay;
	return true;
}

void UGameManager::InitManager()
{
	//?

}

