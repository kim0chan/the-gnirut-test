// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WaitingPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AWaitingPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	bool isReady();
	void reverseIsReady();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void InitPlayerName(const uint32 key);

protected:
	UFUNCTION(Server, Unreliable)
	void ServerReverseIsReady();

	UFUNCTION()
	void OnRep_ReverseIsReady();

	void UpdatePlayerReady();

	UFUNCTION(Client, Reliable)
	void ClientSetPlayerNameFromGameInstance(const uint32& key);

	UFUNCTION(Server, Reliable)
	void ServerSetPlayerNameFromGameInstance(const FString& PlayerName, const uint32& key);

	void SetPlayerNameAndUpdate(const FString& PlayerName, const uint32& key);

	UPROPERTY(ReplicatedUsing = OnRep_ReverseIsReady)
	bool bIsReady = false;
};
