// Fill out your copyright notice in the Description page of Project Settings.


#include "TabkeyPlayerHUD.h"
#include "Components/Button.h"
#include "GnirutPlayerController.h"

void UTabkeyPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &ThisClass::OnLeaveButtonClicked);
	}
}

void UTabkeyPlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();

	// Remove all bindings from the OnClicked event of the LeaveButton
	LeaveButton->OnClicked.RemoveAll(this);
}

void UTabkeyPlayerHUD::ToggleVisibility()
{
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTabkeyPlayerHUD::OnLeaveButtonClicked()
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
