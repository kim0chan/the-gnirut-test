// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerListItem.h"
#include "Components/TextBlock.h"

void UGnirutPlayerListItem::setPlayerNameTextBlock(FText playerName)
{
	if (PlayerNameTextBlock)
	{
		PlayerNameTextBlock->SetText(playerName);
	}
}
