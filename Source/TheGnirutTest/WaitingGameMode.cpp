// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingGameMode.h"
#include "WaitingPlayerController.h"
#include "WaitingGameState.h"
#include "WaitingPlayerState.h"

void AWaitingGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(NewPlayer);
	if (WPC) 
	{
		AWaitingPlayerState* WPS = WPC->GetPlayerState<AWaitingPlayerState>();
		if (WPS)
		{
			if (NewPlayer->GetNetConnection())
			{
				WPS->InitPlayerName(NewPlayer->GetNetConnection()->GetConnectionId());
				//UE_LOG(LogTemp, Display, TEXT("%s"), *(NewPlayer->GetNetConnection()->LowLevelGetRemoteAddress()));
				//UE_LOG(LogTemp, Display, TEXT("%d"), NewPlayer->GetNetConnection()->GetConnectionId());
			}
			else
			{
				WPS->InitPlayerName(0);
			}
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
	if (WGS && WGS->isAllPlayersReady())
	{
		TravelToMainGame();
	}
}

void AWaitingGameMode::TravelToMainGame()
{
	UWorld* world = GetWorld();
	if (world)
	{
		bUseSeamlessTravel = true;
		world->ServerTravel("/Game/Gnirut/BasicMap?listen");
	}
}
