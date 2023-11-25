// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGnirutPlayerController.generated.h"

/**
 *
 */
UCLASS()
class THEGNIRUTTEST_API AAGnirutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAGnirutPlayerController();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ToggleTabMenuVisibility();

	void ReturnToLobby();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UKillLogHUD> PlayerHUDClass;

	UPROPERTY()
	UKillLogHUD* PlayerHUD;
};
