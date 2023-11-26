// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerList.h"
#include "Components/ScrollBox.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "GnirutPlayerListItem.h"

void UGnirutPlayerList::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		AGnirutGameState* GGS = Cast<AGnirutGameState>(world->GetGameState());
		if (GGS)
		{
			PlayerScrollBox->ClearChildren();
			for (APlayerState* PS : GGS->AllPlayerStates)
			{
				AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(PS);
				if (GPS)
				{
					UGnirutPlayerListItem* PLI = CreateWidget<UGnirutPlayerListItem>(this, PlayerListItemClass);
					if (PLI)
					{
						PLI->setPlayerNameTextBlock(FText::FromString(GPS->GetPlayerNickName()));
						// update additional info
						PlayerScrollBox->AddChild(PLI);
						PlayerListItemByPlayerID.Add(GPS->GetPlayerId(), PLI);
					}
				}
			}
		}
	}
}
