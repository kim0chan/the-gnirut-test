// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDefeatHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GnirutPlayerController.h"
#include "GnirutGameState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GnirutPlayerList.h"

void UGameDefeatHUD::SetDefeatedTextBlock(FString AttackerName)
{
	if (DefeatedTextBlock)
	{
		DefeatedTextBlock->SetText(FText::FromString("You were defeated\n by " + AttackerName + "!!"));
	}
}

void UGameDefeatHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (SpectateButton)
	{
		SpectateButton->OnClicked.AddDynamic(this, &ThisClass::OnSpectateButtonClicked);
	}

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &ThisClass::OnLeaveButtonClicked);
	}

	UWorld* world = GetWorld();
	if (world)
	{
		AGnirutGameState* GGS = Cast<AGnirutGameState>(world->GetGameState());
		int NumberOfHumanPlayers = GGS ? GGS->GetNumberOfHumanPlayers() : 1;

		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UGnirutPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UGnirutPlayerList* GPL = Cast<UGnirutPlayerList>(UW);
			if (GPL)
			{
				GPL->UpdatePlayerList();
				GPL->UpdateNumberOfHumanPlayers(NumberOfHumanPlayers);
			}
		}
	}
}

void UGameDefeatHUD::OnSpectateButtonClicked()
{
	if (SpectateButton)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			AGnirutPlayerController* GPC = Cast<AGnirutPlayerController>(world->GetFirstPlayerController());
			if (GPC)
			{
				GPC->StartSpectate();
			}
		}
	}
}

void UGameDefeatHUD::OnLeaveButtonClicked()
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
