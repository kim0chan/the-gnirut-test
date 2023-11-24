// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGnirutTestGameState.h"
#include "KillLogHUD.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ATheGnirutTestGameState::ATheGnirutTestGameState()
{
	NumberOfAIPlayers = 0;
	NumberOfHumanPlayers = 0;
}

void ATheGnirutTestGameState::SetKillLogInfo(AGnirutHumanPlayer* Attacker, AGnirutHumanPlayer* Victim)
{
	FString AttackerNickname = (Attacker) ? Attacker->GetPlayerState<AGnirutPlayerState>()->GetPlayerNickName() : "A player";
	FString VictimNickname = "an AI";

	if (Victim)
	{
		for (APlayerState* PS : PlayerArray)
		{
			AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(PS);
			APawn* PossessingPawn = GPS->GetPawn();
			if (!PossessingPawn)	continue;	// Possessing Pawn Is Dead.
			if (Victim->GetUniqueID() == PossessingPawn->GetUniqueID())
			{
				VictimNickname = GPS->GetPlayerNickName();
			}
		}
	}

	FString KillLogMessage = FString::Printf(TEXT("%s has slain %s."), *AttackerNickname, *VictimNickname);
	//UE_LOG(LogTemp, Display, TEXT("%s"), *KillLogMessage);
	UpdateKillLogInfo(KillLogMessage);
}

void ATheGnirutTestGameState::UpdateKillLogInfo(const FString& KillLogMessage)
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UKillLogHUD::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UKillLogHUD* UKL = Cast<UKillLogHUD>(UW);
			if (UKL)
			{
				UKL->OnKills(KillLogMessage);
			}
		}
	}
}

void ATheGnirutTestGameState::DecrementPlayerCounts_Implementation(bool isAIPlayer)
{
	if (isAIPlayer)
	{
		NumberOfAIPlayers--;
		//UE_LOG(LogTemp, Display, TEXT("[kill log] an AI Player got killed! [%d]"), NumberOfAIPlayers);
	}
	else
	{
		NumberOfHumanPlayers--;
		//UE_LOG(LogTemp, Display, TEXT("[kill log] a Human Player got killed! [%d]"), NumberOfHumanPlayers);
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
	//UE_LOG(LogTemp, Display, TEXT("[Initialization] AI : %d, Human : %d"), NumberOfAIPlayers, NumberOfHumanPlayers);
}

void ATheGnirutTestGameState::PlayerLogin_Implementation()
{
	NumberOfHumanPlayers++;
	//UE_LOG(LogTemp, Display, TEXT("[Login] A player has entered the game. There are %d"), NumberOfHumanPlayers);
}

void ATheGnirutTestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATheGnirutTestGameState, NumberOfAIPlayers, COND_None);
	DOREPLIFETIME_CONDITION(ATheGnirutTestGameState, NumberOfHumanPlayers, COND_None);
}

int32 ATheGnirutTestGameState::GetNumberOfHumanPlayers() {
	return NumberOfHumanPlayers;
}
int32 ATheGnirutTestGameState::GetNumberOfAIPlayers() {
	return NumberOfAIPlayers;
}

