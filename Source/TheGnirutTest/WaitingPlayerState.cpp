// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerState.h"
#include "PlayerList.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool AWaitingPlayerState::isReady()
{
	return bIsReady;
}

void AWaitingPlayerState::reverseIsReady()
{
	ServerReverseIsReady();
}

void AWaitingPlayerState::ServerReverseIsReady_Implementation()
{
	MulticastReverseIsReady();
}

void AWaitingPlayerState::MulticastReverseIsReady_Implementation()
{
	bIsReady = !bIsReady;
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
				UPL->UpdatePlayerReady(GetPlayerId(), bIsReady);
			}
		}
	}
}
