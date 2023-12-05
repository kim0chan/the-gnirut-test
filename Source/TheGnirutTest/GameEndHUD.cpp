// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GnirutPlayerController.h"
#include "GnirutGameMode.h"
#include "GnirutGameState.h"

void UGameEndHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackToWaitingButton)
	{
		BackToWaitingButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToWaitingButtonClicked);
	}

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &ThisClass::OnLeaveButtonClicked);
	}
}

void UGameEndHUD::SetBackToWaitingButtonVisibility(ESlateVisibility InVisibility)
{
	BackToWaitingButton->SetVisibility(InVisibility);
}

void UGameEndHUD::SetWinnerTextBlock(FString WinnerName)
{
	if (WinnerTextBlock)
	{
		WinnerTextBlock->SetText(FText::FromString("The Winner is " + WinnerName + "!!"));
	}
}

void UGameEndHUD::SetVictoryConditionTextBlock(EVictoryCondition Condition)
{
	if (VictoryConditionTextBlock)
	{
		FString VCString = "Victory Condition: ";
		switch (Condition)
		{
		case EVictoryCondition::VC_LastManStanding:
			VCString.Append("The Last Man Standing");
			break;
		case EVictoryCondition::VC_GetItem:
			VCString.Append("VC_GetItem"); // 추후 수정
			break;
		default:
			break;
		}
		VictoryConditionTextBlock->SetText(FText::FromString(VCString));
	}
}

void UGameEndHUD::OnBackToWaitingButtonClicked()
{
	if (BackToWaitingButton)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			AGnirutGameMode* GGM = Cast<AGnirutGameMode>(world->GetAuthGameMode());
			if (GGM)
			{
				GGM->TravleToWaiting();
			}
		}
	}	
}

void UGameEndHUD::OnLeaveButtonClicked()
{
	if (LeaveButton)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			AGnirutPlayerController* GPC = Cast<AGnirutPlayerController>(world->GetFirstPlayerController());
			if (GPC)
			{
				GPC->ReturnToLobby();
			}
		}
	}
}
