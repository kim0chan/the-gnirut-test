// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerList.h"
#include "Components/ScrollBox.h"
#include "WaitingGameState.h"
#include "WaitingPlayerState.h"
#include "WaitingPlayerListItem.h"

void UWaitingPlayerList::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		AWaitingGameState* WGS = Cast<AWaitingGameState>(world->GetGameState());
		if (WGS)
		{
			PlayerScrollBox->ClearChildren();
			for (APlayerState* PS : WGS->AllPlayerStates)
			{
				AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(PS);
				if (WPS)
				{						
					UWaitingPlayerListItem* PLI = CreateWidget<UWaitingPlayerListItem>(this, PlayerListItemClass);
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

void UWaitingPlayerList::UpdatePlayerReady(int32 PlayerID, bool isReady)
{
	UWaitingPlayerListItem** PLI = PlayerListItemByPlayerID.Find(PlayerID);
	if (PLI)
	{
		(*PLI)->setIsReadyTextBlock(isReady);
	}
}
