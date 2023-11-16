// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerState.h"
#include "WaitingGameMode.h"
#include "PlayerList.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"

bool AWaitingPlayerState::isReady()
{
	return bIsReady;
}

void AWaitingPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaitingPlayerState, bIsReady);
}

void AWaitingPlayerState::reverseIsReady()
{
	ServerReverseIsReady();
}

void AWaitingPlayerState::ServerReverseIsReady_Implementation()
{
	bIsReady = !bIsReady;
	UpdatePlayerReady();	
}

void AWaitingPlayerState::OnRep_ReverseIsReady()
{
	UpdatePlayerReady();
}

void AWaitingPlayerState::UpdatePlayerReady()
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
				UPL->UpdatePlayerReady(GetPlayerId(), bIsReady);
			}
		}

		if (HasAuthority()) 
		{
			AWaitingGameMode* WGM = Cast<AWaitingGameMode>(world->GetAuthGameMode());
			if (WGM)
			{
				WGM->CheckToTravelMainGame();
			}
		}
	}
}
