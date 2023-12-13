// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutGameState.h"
#include "KillLogHUD.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GnirutPlayerList.h"
#include "GnirutPlayerController.h"
#include "GnirutPlayerState.h"
#include "GnirutHumanPlayer.h"

AGnirutGameState::AGnirutGameState()
{ 
	NumberOfAIPlayers = 0;
	NumberOfHumanPlayers = 0;
	IsGameEnded = false;
}

void AGnirutGameState::OnRep_NumberOfHumanPlayers()
{
	UpdateNumberOfHumanPlayers();
}

void AGnirutGameState::UpdateNumberOfHumanPlayers()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UGnirutPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UGnirutPlayerList* GPL = Cast<UGnirutPlayerList>(UW);
			if (GPL)
			{
				GPL->UpdateNumberOfHumanPlayers(NumberOfHumanPlayers);
			}
		}
	}
}

void AGnirutGameState::SetKillLogInfo(AGnirutHumanPlayer* Attacker, AGnirutHumanPlayer* Victim)
{
	FString AttackerNickname = (Attacker) ? Attacker->GetPlayerState<AGnirutPlayerState>()->GetPlayerName() : "A player";
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
				VictimNickname = GPS->GetPlayerName();
			}
		}
	}

	FString KillLogMessage = FString::Printf(TEXT("%s has slain %s."), *AttackerNickname, *VictimNickname);
	//UE_LOG(LogTemp, Display, TEXT("%s"), *KillLogMessage);
	UpdateKillLogInfo(KillLogMessage);
}

void AGnirutGameState::UpdateKillLogInfo(const FString& KillLogMessage)
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

void AGnirutGameState::DecrementPlayerCounts_Implementation(bool isAIPlayer)
{
	if (isAIPlayer)
	{
		NumberOfAIPlayers--;
		//UE_LOG(LogTemp, Display, TEXT("[kill log] an AI Player got killed! [%d]"), NumberOfAIPlayers);
	}
	else
	{
		NumberOfHumanPlayers--;
		UpdateNumberOfHumanPlayers();
		//UE_LOG(LogTemp, Display, TEXT("[kill log] a Human Player got killed! [%d]"), NumberOfHumanPlayers);
	}

	CheckGameEnd_Implementation();
}

void AGnirutGameState::CheckGameEnd_Implementation()
{
	AGnirutPlayerState* Winner = nullptr;
	EVictoryCondition Condition = EVictoryCondition::VC_None;

	if (NumberOfHumanPlayers <= 1)
	{
		Condition = EVictoryCondition::VC_LastManStanding;
		for (APlayerState* PS : PlayerArray)
		{
			AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(PS);
			if (GPS && GPS->GetIsAlive())
			{	
				Winner = GPS;
				break;
			}
		}
	}

	if (Winner && Condition != EVictoryCondition::VC_None) 
		HandleGameEnd(Winner, Condition);
}

void AGnirutGameState::CheckGameEndByItem_Implementation()
{
	AGnirutPlayerState* Winner = nullptr;
	EVictoryCondition Condition = EVictoryCondition::VC_None;

	Condition = EVictoryCondition::VC_GetItem;
	for (APlayerState* PS : PlayerArray)
	{
		AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(PS);
		if (GPS && GPS->GetIsHoldingItem())
		{
			Winner = GPS;
			break;
		}
	}

	if (Winner && Condition != EVictoryCondition::VC_None)
		HandleGameEnd(Winner, Condition);
}

void AGnirutGameState::HandleGameEnd_Implementation(AGnirutPlayerState* WinningPlayer, EVictoryCondition VictoryCondition)
{
	if (IsGameEnded)	return;
	UWorld* world = GetWorld();
	if (world)
	{
		AGnirutPlayerController* GPC = Cast<AGnirutPlayerController>(world->GetFirstPlayerController());
		if (GPC && GPC->IsLocalPlayerController())
		{
			GPC->HandleGameEnd(WinningPlayer, VictoryCondition);
		}
	}
	IsGameEnded = true;
}

void AGnirutGameState::InitPlayerCounts_Implementation(int32 numAI, int32 numHuman)
{
	NumberOfAIPlayers = numAI;
	//NumberOfHumanPlayers = numHuman;
	//UpdateNumberOfHumanPlayers();
	//UE_LOG(LogTemp, Display, TEXT("[Initialization] AI : %d, Human : %d"), NumberOfAIPlayers, NumberOfHumanPlayers);
}

void AGnirutGameState::PlayerLogin_Implementation()
{
	NumberOfHumanPlayers++;
	UpdateNumberOfHumanPlayers();
	//UE_LOG(LogTemp, Display, TEXT("[Login] A player has entered the game. There are %d"), NumberOfHumanPlayers);
}

void AGnirutGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AGnirutGameState, NumberOfAIPlayers, COND_None);
	DOREPLIFETIME_CONDITION(AGnirutGameState, NumberOfHumanPlayers, COND_None);
	DOREPLIFETIME(AGnirutGameState, AllPlayerStates);
}

int32 AGnirutGameState::GetNumberOfHumanPlayers() {
	return NumberOfHumanPlayers;
}
int32 AGnirutGameState::GetNumberOfAIPlayers() {
	return NumberOfAIPlayers;
}

void AGnirutGameState::UpdateAllPlayerStates()
{
	AllPlayerStates.Empty();
	for (APlayerState* PS : PlayerArray) {
		AllPlayerStates.Add(PS);
	}

	// for server
	UpdatePlayerList();
}

void AGnirutGameState::OnRep_AllPlayerState()
{
	// for client
	UpdatePlayerList();
}

void AGnirutGameState::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UGnirutPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UGnirutPlayerList* GPL = Cast<UGnirutPlayerList>(UW);
			if (GPL)
			{
				GPL->UpdatePlayerList();
			}
		}
	}
}

