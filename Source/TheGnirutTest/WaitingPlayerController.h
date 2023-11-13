// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WaitingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AWaitingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWaitingPlayerController();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void CreatePlayerHUD();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWaitingPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	UWaitingPlayerHUD* PlayerHUD;
	
};
