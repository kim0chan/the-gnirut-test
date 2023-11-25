#include "WaitingPlayerHUD.h"
#include "WaitingPlayerState.h"
#include "WaitingGameState.h"
#include "WaitingPlayerController.h"
#include "Components/Button.h"

void UWaitingPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ReadyButton)
	{
		ReadyButton->OnClicked.AddDynamic(this, &ThisClass::OnReadyButtonClicked);
	}

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &ThisClass::OnLeaveButtonClicked);
	}
}

void UWaitingPlayerHUD::OnReadyButtonClicked()
{
	if (ReadyButton)
	{
		isReady = !isReady;
		ReadyButton->SetIsEnabled(!isReady);
		AWaitingPlayerState* WPS = Cast<AWaitingPlayerState>(GetOwningPlayerState());
		if (WPS)
		{
			WPS->reverseIsReady();
		}
	}
}

void UWaitingPlayerHUD::OnLeaveButtonClicked()
{
	if (LeaveButton)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			AWaitingPlayerController* WPC = Cast<AWaitingPlayerController>(world->GetFirstPlayerController());
			if (WPC)
			{
				WPC->ReturnToLobby();
			}
		}
	}
}
