// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGnirutTestGameState.h"
#include "Net/UnrealNetwork.h"

ATheGnirutTestGameState::ATheGnirutTestGameState()
{
	NumberOfAIPlayers = 0;
	NumberOfHumanPlayers = 0;
}

void ATheGnirutTestGameState::DecrementPlayerCounts_Implementation(bool isAIPlayer)
{
	if (isAIPlayer)
	{
		NumberOfAIPlayers--;
		UE_LOG(LogTemp, Display, TEXT("[kill log] an AI Player got killed! [%d]"), NumberOfAIPlayers);
	}
	else
	{
		NumberOfHumanPlayers--;
		UE_LOG(LogTemp, Display, TEXT("[kill log] a Human Player got killed! [%d]"), NumberOfHumanPlayers);
	}

	CheckGameEnd_Implementation();
}

void ATheGnirutTestGameState::CheckGameEnd_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("[GameState>CheckGameEnd] AI: %d, Human: %d"), NumberOfAIPlayers, NumberOfHumanPlayers);
	if (NumberOfHumanPlayers <= 1)
	{
		UE_LOG(LogTemp, Display, TEXT("GAME ENDED."));
	}
}

void ATheGnirutTestGameState::InitPlayerCounts_Implementation(int32 numAI, int32 numHuman)
{
	NumberOfAIPlayers = numAI;
	NumberOfHumanPlayers = numHuman;
	UE_LOG(LogTemp, Display, TEXT("[Initialization] AI : %d, Human : %d"), NumberOfAIPlayers, NumberOfHumanPlayers);
}

void ATheGnirutTestGameState::PlayerLogin_Implementation()
{
	NumberOfHumanPlayers++;
	UE_LOG(LogTemp, Display, TEXT("[Login] A player has entered the game. There are %d"), NumberOfHumanPlayers);
}

void ATheGnirutTestGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicated 변수 지정
	DOREPLIFETIME_CONDITION(ATheGnirutTestGameState, NumberOfAIPlayers, COND_None);
	DOREPLIFETIME_CONDITION(ATheGnirutTestGameState, NumberOfHumanPlayers, COND_None);
}