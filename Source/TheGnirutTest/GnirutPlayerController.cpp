// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerController.h"
#include "KillLogHUD.h"
#include "TabkeyPlayerHUD.h"
#include "GameEndHUD.h"
#include "GnirutGameMode.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGnirutPlayerController::AGnirutPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
	GameEndHUDClass = nullptr;
	GameEndHUD = nullptr;
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

void AGnirutPlayerController::HandleGameEnd(AGnirutPlayerState* WinningPlayer, EVictoryCondition VictoryCondition)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	
	if (IsLocalController() && GameEndHUDClass && GetPawn()) {
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
