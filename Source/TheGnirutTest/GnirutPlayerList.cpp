// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerList.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "GnirutPlayerListItem.h"
#include "GnirutGameInstance.h"

void UGnirutPlayerList::UpdateNumberOfHumanPlayers(int num)
{
	if (NumberOfHumanPlayersTextBlock)
	{
		NumberOfHumanPlayersTextBlock->SetText(FText::FromString("Human: " + FString::FromInt(num)));
	}
}

void UGnirutPlayerList::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		AGnirutGameState* GGS = Cast<AGnirutGameState>(world->GetGameState());
		if (GGS)
		{
			PlayerScrollBox->ClearChildren();
			for (APlayerState* PS : GGS->PlayerArray)
			{
				AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(PS);
				if (GPS)
				{
					UGnirutPlayerListItem* PLI = CreateWidget<UGnirutPlayerListItem>(this, PlayerListItemClass);
					if (PLI)
					{
						if (GPS->GetPlayerController()) {
							PLI->SetIsLocalPlayer(GPS->GetPlayerController()->IsLocalController());
						}
						PLI->SetPlayerNameTextBlock(FText::FromString(GPS->GetPlayerName()));
						PLI->SetIsAlive(GPS->GetIsAlive());
						PLI->SetKillsTextBlock(GPS->GetHumanPlayerKills(), GPS->GetAIPlayerKills());
						// update additional info
						PlayerScrollBox->AddChild(PLI);
						PlayerListItemByPlayerID.Add(GPS->GetPlayerId(), PLI);
					}
				}
			}
		}
	}
}

void UGnirutPlayerList::UpdatePlayerAlive(int32 PlayerID, bool isAlive)
{
	UGnirutPlayerListItem** PLI = PlayerListItemByPlayerID.Find(PlayerID);
	if (PLI)
	{
		(*PLI)->SetIsAlive(isAlive);
	}
}

void UGnirutPlayerList::UpdateKills(int32 PlayerID, int32 HumanPlayerKills, int32 AIPlayerKills)
{
	UGnirutPlayerListItem** PLI = PlayerListItemByPlayerID.Find(PlayerID);
	if (PLI)
	{
		(*PLI)->SetKillsTextBlock(HumanPlayerKills, AIPlayerKills);
	}
}
