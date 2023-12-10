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
			FSlateColor color = FColor(255, 255, 0);
			PlayerNameTextBlock->SetColorAndOpacity(color);
			IsAliveTextBlock->SetColorAndOpacity(color);
			KillsTextBlock->SetColorAndOpacity(color);
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

			FSlateColor color = bIsLocalPlayer ? FColor(110, 110, 20) : FColor(120, 120, 120);
			PlayerNameTextBlock->SetColorAndOpacity(color);
			IsAliveTextBlock->SetColorAndOpacity(color);
			KillsTextBlock->SetColorAndOpacity(color);
		}
	}
}

void UGnirutPlayerListItem::SetIsLocalPlayer(bool isLocalPlayer)
{
	bIsLocalPlayer = isLocalPlayer;
}

void UGnirutPlayerListItem::SetKillsTextBlock(int32 HumanPlayerKills, int32 AIPlayerKills)
{
	if (KillsTextBlock) {
		KillsTextBlock->SetText(FText::FromString("killed " + FString::FromInt(HumanPlayerKills) + " Human, " + FString::FromInt(AIPlayerKills) + " AI"));
	}
}
