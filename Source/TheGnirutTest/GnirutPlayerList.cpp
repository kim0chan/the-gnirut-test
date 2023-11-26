// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerList.h"
#include "Components/ScrollBox.h"
#include "TheGnirutTestGameState.h"
#include "GnirutPlayerState.h"
#include "GnirutPlayerListItem.h"

void UGnirutPlayerList::UpdatePlayerList()
{
	UWorld* world = GetWorld();
	if (world)
	{
		ATheGnirutTestGameState* GGS = Cast<ATheGnirutTestGameState>(world->GetGameState());
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
