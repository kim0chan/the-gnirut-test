#include "WaitingPlayerHUD.h"
#include "WaitingPlayerState.h"
#include "WaitingGameState.h"
#include "Components/Button.h"

void UWaitingPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ReadyButton)
	{
		ReadyButton->OnClicked.AddDynamic(this, &ThisClass::OnReadyButtonClicked);
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
