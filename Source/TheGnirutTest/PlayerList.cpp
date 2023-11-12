// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerList.h"
#include "Components/ScrollBox.h"
#include "WaitingGameState.h"
#include "WaitingPlayerState.h"
#include "PlayerListItem.h"

void UPlayerList::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		AWaitingGameState* WGS = Cast<AWaitingGameState>(world->GetGameState());
		if (WGS)
		{
			PlayerScrollBox->ClearChildren();
			for (APlayerState* PS : WGS->PlayerArray)
			{
				AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(PS);
				if (WPS)
				{						
					UPlayerListItem* PLI = Cast<UPlayerListItem>(CreateWidget<UPlayerListItem>(this, PlayerListItemClass));
					if (PLI)
					{
						PLI->setPlayerNameTextBlock(FText::FromString(WPS->GetPlayerName()));
						PLI->setIsReadyTextBlock(WPS->isReady());
						PlayerScrollBox->AddChild(PLI);
						PlayerListItemByPlayerID.Add( WPS->GetPlayerId() , PLI );
					}
				}
			}
		}
	}
}

void UPlayerList::UpdatePlayerReady(int32 PlayerID, bool isReady)
{
	UPlayerListItem** PLI = PlayerListItemByPlayerID.Find(PlayerID);
	if (PLI)
	{
		(*PLI)->setIsReadyTextBlock(isReady);
	}
}
