// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GnirutHumanPlayer.h"
#include "GnirutPlayerState.h"
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TheGnirutTestGameState.generated.h"

/**
 *
 */
UCLASS()
class THEGNIRUTTEST_API ATheGnirutTestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATheGnirutTestGameState();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game State")
	int32 NumberOfAIPlayers;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game State")
	int32 NumberOfHumanPlayers;

	UFUNCTION(Category = "Game State")
	void SetKillLogInfo(AGnirutHumanPlayer* Attacker, AGnirutHumanPlayer* Victim);

	UFUNCTION(Category = "Game State")
	void UpdateKillLogInfo(const FString& KillLogMessage);

	UFUNCTION(Server, Reliable)
	void DecrementPlayerCounts(bool isAIPlayer);
	void DecrementPlayerCounts_Implementation(bool isAIPlayer);

	UFUNCTION(Server, Reliable)
	void CheckGameEnd();
	void CheckGameEnd_Implementation();

	UFUNCTION(Server, Reliable)
	void InitPlayerCounts(int32 numAI, int32 numHuman);
	void InitPlayerCounts_Implementation(int32 numAI, int32 numHuman);

	UFUNCTION(Server, Reliable)
	void PlayerLogin();
	void PlayerLogin_Implementation();

	int32 GetNumberOfHumanPlayers();
	int32 GetNumberOfAIPlayers();


protected:
	// Replicated
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
