// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerListItem.h"
#include "Components/TextBlock.h"

void UWaitingPlayerListItem::setPlayerNameTextBlock(FText playerName)
{
	if (PlayerNameTextBlock)
	{
		PlayerNameTextBlock->SetText(playerName);
	}
}

void UWaitingPlayerListItem::setIsReadyTextBlock(bool isReady)
{
	if (IsReadyTextBlock)
	{
		if (isReady) {
			IsReadyTextBlock->SetText(FText::FromString(TEXT("O")));
		}
		else {
			IsReadyTextBlock->SetText(FText::FromString(TEXT("X")));
		}
	}	
}
