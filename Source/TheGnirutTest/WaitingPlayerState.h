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
	
protected:
	UFUNCTION(Server, Unreliable)
	void ServerReverseIsReady();

	UFUNCTION()
	void OnRep_ReverseIsReady();

	void UpdatePlayerReady();

	UPROPERTY(ReplicatedUsing = OnRep_ReverseIsReady)
	bool bIsReady = false;
};
