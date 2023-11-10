// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListItem.h"
#include "Components/TextBlock.h"

void UPlayerListItem::setPlayerNameTextBlock(FText playerName)
{
	if (PlayerNameTextBlock)
	{
		PlayerNameTextBlock->SetText(playerName);
	}
}

void UPlayerListItem::setIsReadyTextBlock(bool isReady)
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
