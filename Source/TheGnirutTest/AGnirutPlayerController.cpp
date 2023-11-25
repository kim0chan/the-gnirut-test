// Fill out your copyright notice in the Description page of Project Settings.


#include "AGnirutPlayerController.h"
#include "KillLogHUD.h"
#include "TabkeyPlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "TheGnirutTestGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AAGnirutPlayerController::AAGnirutPlayerController()
{
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
}

void AAGnirutPlayerController::BeginPlay()
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

void AAGnirutPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void AAGnirutPlayerController::ToggleTabMenuVisibility()
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

void AAGnirutPlayerController::ReturnToLobby()
{
	ClientTravel(TEXT("/Game/Lobby/LobbyMap"), ETravelType::TRAVEL_Absolute);
}
