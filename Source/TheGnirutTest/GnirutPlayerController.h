// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GnirutPlayerController.generated.h"

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

	void ReturnToLobby();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UKillLogHUD> PlayerHUDClass;

	UPROPERTY()
	UKillLogHUD* PlayerHUD;
};
