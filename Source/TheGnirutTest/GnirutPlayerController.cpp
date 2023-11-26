// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerController.h"
#include "KillLogHUD.h"
#include "TabkeyPlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "GnirutGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGnirutPlayerController::AGnirutPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
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

void AGnirutPlayerController::ReturnToLobby()
{
	ClientTravel(TEXT("/Game/Lobby/LobbyMap"), ETravelType::TRAVEL_Absolute);
}
