// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingPlayerState.h"
#include "WaitingGameMode.h"
#include "GnirutGameInstance.h"
#include "WaitingPlayerList.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"

bool AWaitingPlayerState::isReady()
{
	return bIsReady;
}

void AWaitingPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaitingPlayerState, bIsReady);
}

void AWaitingPlayerState::InitPlayerName(const uint32 key)
{
	if (GetOwningController()->IsLocalPlayerController()) {
		if (UGnirutGameInstance* GGI = GetGameInstance<UGnirutGameInstance>()) {
			FString name = GGI->GetPlayerName();
			SetPlayerNameAndUpdate(name, key);
		}
	}
	else {
		ClientSetPlayerNameFromGameInstance(key);
	}
}

void AWaitingPlayerState::ClientSetPlayerNameFromGameInstance_Implementation(const uint32& key)
{
	if (UGnirutGameInstance* GGI = GetGameInstance<UGnirutGameInstance>()) {
		FString name = GGI->GetPlayerName();
		//UE_LOG(LogTemp, Display, TEXT("%s"), *name);
		if (!name.IsEmpty()) {
			SetPlayerName(name);
		}
		ServerSetPlayerNameFromGameInstance(name, key);
	}
}

void AWaitingPlayerState::ServerSetPlayerNameFromGameInstance_Implementation(const FString& PlayerName, const  uint32& key)
{
	SetPlayerNameAndUpdate(PlayerName, key);
}

void AWaitingPlayerState::SetPlayerNameAndUpdate(const FString& PlayerName, const uint32& key)
{
	if (!PlayerName.IsEmpty()) {
		SetPlayerName(PlayerName);
		UGnirutGameInstance* GGI = Cast<UGnirutGameInstance>(GetGameInstance());
		if (GGI)
		{
			GGI->PlayerNameMap.Add(key, PlayerName);
		}
	}

	UWorld* world = GetWorld();
	if (world)
	{
		AWaitingGameMode* WGM = Cast<AWaitingGameMode>(world->GetAuthGameMode());
		if (WGM)
		{
			WGM->UpdatePlayerList();
		}
	}
}

void AWaitingPlayerState::reverseIsReady()
{
	ServerReverseIsReady();
}

void AWaitingPlayerState::ServerReverseIsReady_Implementation()
{
	bIsReady = !bIsReady;
	UpdatePlayerReady();	
}

void AWaitingPlayerState::OnRep_ReverseIsReady()
{
	UpdatePlayerReady();
}

void AWaitingPlayerState::UpdatePlayerReady()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UWaitingPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UWaitingPlayerList* WPL = Cast<UWaitingPlayerList>(UW);
			if (WPL)
			{
				WPL->UpdatePlayerReady(GetPlayerId(), bIsReady);
			}
		}

		if (HasAuthority()) 
		{
			AWaitingGameMode* WGM = Cast<AWaitingGameMode>(world->GetAuthGameMode());
			if (WGM)
			{
				WGM->CheckToTravelMainGame();
			}
		}
	}
}
