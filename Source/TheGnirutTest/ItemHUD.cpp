// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHUD.h"
#include "Components/TextBlock.h"

void UItemHUD::OnRemainingTimeChange(const FString& NewRemainingTime)
{
	;
}

void UItemHUD::UpdateTextBlock(const FString& Content)
{
	if (RemainingTimeTextBlock)
	{
		RemainingTimeTextBlock->SetText(FText::FromString(Content));
	}
}