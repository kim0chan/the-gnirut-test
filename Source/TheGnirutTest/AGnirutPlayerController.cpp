// Fill out your copyright notice in the Description page of Project Settings.


#include "AGnirutPlayerController.h"
#include "KillLogHUD.h"
#include "Blueprint/UserWidget.h"

AAGnirutPlayerController::AAGnirutPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
}

void AAGnirutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UKillLogHUD>(this, PlayerHUDClass);
		if (PlayerHUD) {
			PlayerHUD->AddToViewport();
			PlayerHUD->HideKillLogTextBlock();
		}
	}
}

void AAGnirutPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}
