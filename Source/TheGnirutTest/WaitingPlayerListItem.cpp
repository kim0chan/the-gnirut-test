// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerListItem.h"
#include "Components/TextBlock.h"

void UWaitingPlayerListItem::SetPlayerNameTextBlock(FText playerName)
{
	if (PlayerNameTextBlock)
	{
		PlayerNameTextBlock->SetText(playerName);
		if (bIsLocalPlayer)
		{
			PlayerNameTextBlock->SetColorAndOpacity(FSlateColor(FColor(255, 255, 0)));
		}
	}
}

void UWaitingPlayerListItem::SetIsReadyTextBlock(bool isReady)
{
	if (IsReadyTextBlock)
	{
		if (isReady) {
			IsReadyTextBlock->SetText(FText::FromString(TEXT("O")));
		}
		else {
			IsReadyTextBlock->SetText(FText::FromString(TEXT("X")));
		}
		if (bIsLocalPlayer)
		{
			IsReadyTextBlock->SetColorAndOpacity(FSlateColor(FColor(255, 255, 0)));
		}
	}	
}

void UWaitingPlayerListItem::SetIsLocalPlayer(bool isLocalPlayer)
{
	bIsLocalPlayer = isLocalPlayer;
}
