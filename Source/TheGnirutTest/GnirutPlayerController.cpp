// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerController.h"
#include "KillLogHUD.h"
#include "TabkeyPlayerHUD.h"
#include "GameDefeatHUD.h"
#include "GameEndHUD.h"
#include "GnirutPlayerList.h"
#include "GnirutGameMode.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "GnirutSpectatorPawn.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGnirutPlayerController::AGnirutPlayerController()
{
	PlayerHUDClass = nullptr;
	GameEndHUDClass = nullptr;
	GameDefeatHUDClass = nullptr;
	PlayerHUD = nullptr;
	GameEndHUD = nullptr;
	GameDefeatHUD = nullptr;
}

void AGnirutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UKillLogHUD>(this, PlayerHUDClass);
		if (PlayerHUD) {
			PlayerHUD->AddToViewport();
			PlayerHUD->HideKillLogTextBlock();
		}
	}
}

void AGnirutPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	if (GameDefeatHUD)
	{
		GameDefeatHUD->RemoveFromParent();
		GameDefeatHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void AGnirutPlayerController::ToggleTabMenuVisibility()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UTabkeyPlayerHUD::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UTabkeyPlayerHUD* TPH = Cast<UTabkeyPlayerHUD>(UW);
			if (TPH)
			{
				TPH->ToggleVisibility();
				SetShowMouseCursor(!ShouldShowMouseCursor());
			}
		}
	}
}

void AGnirutPlayerController::HandleGameDefeat_Implementation(AGnirutPlayerState* Attacker)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromViewport();
	}
	if (GameEndHUD == nullptr && GameDefeatHUDClass)
	{
		GameDefeatHUD = CreateWidget<UGameDefeatHUD>(this, GameDefeatHUDClass);
		if (GameDefeatHUD) 
		{
			SetShowMouseCursor(true);


			GameDefeatHUD->AddToViewport();
			GameDefeatHUD->SetDefeatedTextBlock(Attacker->GetPlayerName());
		}
	}
}

void AGnirutPlayerController::StartSpectate()
{
	if (GameDefeatHUD)
	{
		GameDefeatHUD->RemoveFromViewport();
		GameDefeatHUD->RemoveFromParent();
		GameDefeatHUD = nullptr;
	}
	if (PlayerHUD)
	{
		SetShowMouseCursor(false);
		PlayerHUD->AddToViewport();
	}
}

void AGnirutPlayerController::HandleGameEnd(AGnirutPlayerState* WinningPlayer, EVictoryCondition VictoryCondition)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	if (GameDefeatHUD)
	{
		GameDefeatHUD->RemoveFromViewport();
		GameDefeatHUD->RemoveFromParent();
		GameDefeatHUD = nullptr;
	}

	if (IsLocalController() && GameEndHUDClass && GetPawn()) {
		SetShowMouseCursor(true);

		GameEndHUD = CreateWidget<UGameEndHUD>(this, GameEndHUDClass);
		if (GameEndHUD) {
			GameEndHUD->SetWinnerTextBlock(WinningPlayer->GetPlayerName());
			GameEndHUD->SetVictoryConditionTextBlock(VictoryCondition);
			if (!HasAuthority()) GameEndHUD->SetBackToWaitingButtonVisibility(ESlateVisibility::Collapsed);
			GameEndHUD->AddToViewport();
		}
	}
}

void AGnirutPlayerController::ReturnToLobby()
{
	ClientTravel(TEXT("/Game/Lobby/LobbyMap"), ETravelType::TRAVEL_Absolute);
}
