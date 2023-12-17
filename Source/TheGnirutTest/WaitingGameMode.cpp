// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingGameMode.h"
#include "WaitingPlayerController.h"
#include "WaitingGameState.h"
#include "WaitingPlayerState.h"

void AWaitingGameMode::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);

	AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(C);
	if (WPC)
	{
		AWaitingPlayerState* WPS = WPC->GetPlayerState<AWaitingPlayerState>();
		if (WPS)
		{
			WPS->InitPlayerName();
		}
	}
}

void AWaitingGameMode::Logout(AController* Exiting)
{
	AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(Exiting);
	if (WPC)
	{
		// delay to call UpdatePlayerList after PlayerArray being updated;
		FTimerHandle LogoutTimer;
		GetWorldTimerManager().SetTimer(
			LogoutTimer,
			this,
			&AWaitingGameMode::UpdatePlayerList,
			0.3f
		);
	}

	Super::Logout(Exiting);
}

void AWaitingGameMode::UpdatePlayerList()
{
	AWaitingGameState* WGS = Cast<AWaitingGameState>(GameState);
	if (WGS)
	{
		WGS->UpdateAllPlayerStates();
	}	
}

void AWaitingGameMode::CheckToTravelMainGame()
{
	AWaitingGameState* WGS = Cast<AWaitingGameState>(GameState);
	if (WGS)
	{
		if(WGS->isAllPlayersReady() && WGS->PlayerArray.Num() >= 2) TravelToMainGame();
	}
}

void AWaitingGameMode::TravelToMainGame()
{
	UWorld* world = GetWorld();
	if (world)
	{
		bUseSeamlessTravel = true;
		//world->ServerTravel("/Game/Gnirut/BasicMap?listen");
		world->ServerTravel("/Game/Gnirut/TestMap?listen");
	}
}
