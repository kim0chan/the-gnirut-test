// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheGnirutTestGameMode.generated.h"

UCLASS(minimalapi)
class ATheGnirutTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// TODO: Get the number of Players in world
	int32 NumAliveGnirutHumanPlayers = 3;

	void CheckGameEnd();

public:
	ATheGnirutTestGameMode();

	void DecrementAliveGnirutHumanPlayers();
};



