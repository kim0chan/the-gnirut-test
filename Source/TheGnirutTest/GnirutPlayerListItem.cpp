// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerListItem.h"
#include "Components/TextBlock.h"

void UGnirutPlayerListItem::SetPlayerNameTextBlock(FText playerName)
{
	if (PlayerNameTextBlock && IsAliveTextBlock)
	{
		PlayerNameTextBlock->SetText(playerName);
		if (bIsLocalPlayer)
		{
			PlayerNameTextBlock->SetColorAndOpacity(FSlateColor(FColor(255, 255, 0)));
			IsAliveTextBlock->SetColorAndOpacity(FSlateColor(FColor(255, 255, 20)));
		}
	}
}

void UGnirutPlayerListItem::SetIsAlive(bool isAlive)
{
	if (PlayerNameTextBlock && IsAliveTextBlock) {
		if (isAlive)
		{
			IsAliveTextBlock->SetText(FText::FromString("(alive)"));
		}
		else
		{
			IsAliveTextBlock->SetText(FText::FromString("(dead)"));
			if (bIsLocalPlayer)
			{
				PlayerNameTextBlock->SetColorAndOpacity(FSlateColor(FColor(110, 110, 20)));
				IsAliveTextBlock->SetColorAndOpacity(FSlateColor(FColor(110, 110, 20)));
			}
			else
			{
				PlayerNameTextBlock->SetColorAndOpacity(FSlateColor(FColor(120, 120, 120)));
				IsAliveTextBlock->SetColorAndOpacity(FSlateColor(FColor(120, 120, 120)));
			}
		}
	}
}

void UGnirutPlayerListItem::SetIsLocalPlayer(bool isLocalPlayer)
{
	bIsLocalPlayer = isLocalPlayer;
}
