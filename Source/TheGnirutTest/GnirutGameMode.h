// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GnirutGameMode.generated.h"

UCLASS(minimalapi)
class AGnirutGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGnirutGameMode();

	int32 NumPlayerStarts;

	TArray<AActor*> PlayerStarts;

	UFUNCTION(BlueprintCallable, Category = "Player")
	int32 GetCurrentPlayerCount();

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	void UpdatePlayerList();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};



