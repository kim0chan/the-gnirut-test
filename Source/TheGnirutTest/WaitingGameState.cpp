// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingGameState.h"
#include "WaitingPlayerState.h"
#include "PlayerList.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool AWaitingGameState::isAllPlayersReady()
{
	for (APlayerState* PS : PlayerArray)
	{
		AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(PS);
		if (WPS && !WPS->isReady())
		{
			return false;
		}
	}

	return true;
}

void AWaitingGameState::UpdatePlayerList()
{
	AllPlayerStates.Empty();
	for (APlayerState* PS : PlayerArray) {
		AllPlayerStates.Add(PS);
	}
}

void AWaitingGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaitingGameState, AllPlayerStates);
}

void AWaitingGameState::OnRep_AllPlayerState()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UPlayerList* UPL = Cast<UPlayerList>(UW);
			if (UPL)
			{
				UPL->UpdatePlayerList();
			}
		}
	}
}
