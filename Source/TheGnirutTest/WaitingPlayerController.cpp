// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerController.h"
#include "WaitingPlayerHUD.h"
#include "Blueprint/UserWidget.h"

AWaitingPlayerController::AWaitingPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AWaitingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UWaitingPlayerHUD>(this, PlayerHUDClass);
		if (PlayerHUD) {
			PlayerHUD->AddToViewport();
		}
	}
}

void AWaitingPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}
