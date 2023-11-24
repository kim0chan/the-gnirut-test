// Fill out your copyright notice in the Description page of Project Settings.


#include "KillLogHUD.h"
#include "Components/TextBlock.h"

void UKillLogHUD::SetKillLogTextBlock(const FString& Content)
{
	if (KillLogTextBlock)
	{
		KillLogTextBlock->SetText(FText::FromString(Content));
		ShowKillLogTextBlock();
		GetWorld()->GetTimerManager().SetTimer(KillLogTimerHandle, this, &UKillLogHUD::HideKillLogTextBlock, KillLogDIsplayDuration, false);
	}
}

void UKillLogHUD::ShowKillLogTextBlock()
{
	if (KillLogTextBlock)
	{
		KillLogTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}
void UKillLogHUD::HideKillLogTextBlock()
{
	if (KillLogTextBlock)
	{
		KillLogTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
}

