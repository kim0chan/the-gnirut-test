// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerController.h"
#include "WaitingPlayerHUD.h"
#include "WaitingGameState.h"
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

	if(IsLocalController())	CreatePlayerHUD();
}

void AWaitingPlayerController::CreatePlayerHUD() {
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UWaitingPlayerHUD>(this, PlayerHUDClass);
		if (PlayerHUD) {
			SetShowMouseCursor(true);

			PlayerHUD->AddToPlayerScreen();
		}

		UWorld* world = GetWorld();
		if (world)
		{
			AWaitingGameState* WGS = Cast<AWaitingGameState>(world->GetGameState());
			if (WGS)
			{
				WGS->UpdatePlayerList();
			}
		}
	}
}

void AWaitingPlayerController::ReturnToLobby()
{
	ClientTravel(TEXT("/Game/Lobby/LobbyMap"), ETravelType::TRAVEL_Absolute);
}

void AWaitingPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		SetShowMouseCursor(false);

		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}
