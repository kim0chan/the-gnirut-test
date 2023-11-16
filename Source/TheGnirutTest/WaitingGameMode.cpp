// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingGameMode.h"
#include "WaitingPlayerController.h"
#include "WaitingGameState.h"

void AWaitingGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(NewPlayer);
	if (WPC) 
	{
		UpdatePlayerList();
	}
}

void AWaitingGameMode::Logout(AController* Exiting)
{
	AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(Exiting);
	if (WPC)
	{
		UpdatePlayerList();
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
		world->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}
