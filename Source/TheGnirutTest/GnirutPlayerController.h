// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GnirutPlayerController.generated.h"

enum class EVictoryCondition : uint8;

/**
 *
 */
UCLASS()
class THEGNIRUTTEST_API AGnirutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGnirutPlayerController();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ToggleTabMenuVisibility();

	void StartSpectate();

	UFUNCTION(Client, Reliable)
	void HandleGameDefeat(class AGnirutPlayerState* Attacker);

	void HandleGameEnd(class AGnirutPlayerState* WinningPlayer, EVictoryCondition VictoryCondition);

	void ReturnToLobby();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UKillLogHUD> PlayerHUDClass;

	UPROPERTY()
	UKillLogHUD* PlayerHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameDefeatHUD> GameDefeatHUDClass;

	UPROPERTY()
	UGameDefeatHUD* GameDefeatHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameEndHUD> GameEndHUDClass;

	UPROPERTY()
	UGameEndHUD* GameEndHUD;
};
