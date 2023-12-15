// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingGameState.h"
#include "WaitingPlayerState.h"
#include "WaitingPlayerList.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool AWaitingGameState::isAllPlayersReady()
{
	for (APlayerState* PS : AllPlayerStates)
	{
		AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(PS);
		if (WPS && !WPS->isReady())
		{
			return false;
		}
	}

	return true;
}

void AWaitingGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaitingGameState, AllPlayerStates);
}

void AWaitingGameState::UpdateAllPlayerStates()
{
	AllPlayerStates.Empty();
	for (APlayerState* PS : PlayerArray) {
		if (!PS) {
			UE_LOG(LogTemp, Error, TEXT("Cant find APlayerState* PS!! in AWaitingGameState"));
			continue;
		}
		AllPlayerStates.Add(PS);
	}

	// for server
	UpdatePlayerList();
}

void AWaitingGameState::OnRep_AllPlayerState()
{
	if (AllPlayerStates.Num() != PlayerArray.Num()) {
		UE_LOG(LogTemp, Error, TEXT("not yet!!"));
		return;
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWaitingGameState::DelayedClientUpdatePlayerList, 0.5f, false);
}

void AWaitingGameState::DelayedClientUpdatePlayerList()
{
	// for client
	UpdatePlayerList();
}

void AWaitingGameState::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UWaitingPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UWaitingPlayerList* WPL = Cast<UWaitingPlayerList>(UW);
			if (WPL)
			{
				WPL->UpdatePlayerList();
			}
		}
	}
}