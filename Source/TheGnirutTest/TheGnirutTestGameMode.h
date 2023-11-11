// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheGnirutTestGameMode.generated.h"

UCLASS(minimalapi)
class ATheGnirutTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void CheckGameEnd();

public:
	ATheGnirutTestGameMode();

	UFUNCTION(BlueprintCallable, Category = "Player")
	int32 GetCurrentPlayerCount();

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};



