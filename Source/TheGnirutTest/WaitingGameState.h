// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WaitingGameState.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AWaitingGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	bool isAllPlayersReady();

	void UpdatePlayerList();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_AllPlayerState();

	UPROPERTY(ReplicatedUsing = OnRep_AllPlayerState)
	TArray<APlayerState*> AllPlayerStates;
};
