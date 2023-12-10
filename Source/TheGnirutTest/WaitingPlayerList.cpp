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
			for (APlayerState* PS : WGS->PlayerArray)
			{
				AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(PS);
				if (WPS)
				{						
					UWaitingPlayerListItem* PLI = CreateWidget<UWaitingPlayerListItem>(this, PlayerListItemClass);
					if (PLI)
					{
						if (WPS->GetPlayerController()) {
							PLI->SetIsLocalPlayer(WPS->GetPlayerController()->IsLocalController());
						}
						PLI->SetPlayerNameTextBlock(FText::FromString(WPS->GetPlayerName()));
						PLI->SetIsReadyTextBlock(WPS->isReady());
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
		(*PLI)->SetIsReadyTextBlock(isReady);
	}
}
