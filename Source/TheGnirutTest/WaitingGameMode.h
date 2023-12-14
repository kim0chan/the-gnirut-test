// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaitingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AWaitingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void GenericPlayerInitialization(AController* C) override;

	virtual void Logout(AController* Exiting) override;

	void UpdatePlayerList();

	void CheckToTravelMainGame();

	void TravelToMainGame();
	
};
