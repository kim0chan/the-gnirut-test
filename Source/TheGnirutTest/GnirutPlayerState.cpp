// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "KillLogHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GnirutPlayerList.h"
#include "GnirutGameInstance.h"
#include "GnirutGameMode.h"

AGnirutPlayerState::AGnirutPlayerState()
{
	bIsAlive = true;
	AIPlayerKills = 0;
	HumanPlayerKills = 0;
	PlayerIndex = 0;
}

int32 AGnirutPlayerState::GetAIPlayerKills() const
{
	return AIPlayerKills;
}

int32 AGnirutPlayerState::GetHumanPlayerKills() const
{
	return HumanPlayerKills;
}

int32 AGnirutPlayerState::GetTotalPlayerKills() const
{
	return GetAIPlayerKills() + GetHumanPlayerKills();
}

int32 AGnirutPlayerState::GetPlayerIndex() const
{
	return PlayerIndex;
}

bool AGnirutPlayerState::GetIsAlive() const
{
	return bIsAlive;
}

bool AGnirutPlayerState::GetIsHoldingItem() const
{
	return bIsHoldingItem;
}

void AGnirutPlayerState::AddAIPlayerKills()
{
	++AIPlayerKills;
	UpdateKills();
	UE_LOG(LogTemp, Warning, TEXT("[Player %s] Killed %d AI(s)."), *GetPlayerName(), GetAIPlayerKills());
}

void AGnirutPlayerState::AddHumanPlayerKills()
{
	++HumanPlayerKills;
	UpdateKills();
	UE_LOG(LogTemp, Warning, TEXT("[Player %s] Killed %d Human(s)."), *GetPlayerName(), GetHumanPlayerKills());
}

void AGnirutPlayerState::InitPlayerName()
{
	if (GetOwningController()->IsLocalPlayerController()) {
		if (UGnirutGameInstance* GGI = GetGameInstance<UGnirutGameInstance>()) {
			FString name = GGI->GetPlayerName();
			SetPlayerNameAndUpdate(name);
		}
	}
	else {
		ClientSetPlayerNameFromGameInstance();
	}
}

void AGnirutPlayerState::ClientSetPlayerNameFromGameInstance_Implementation()
{
	if (UGnirutGameInstance* GGI = GetGameInstance<UGnirutGameInstance>()) {
		FString name = GGI->GetPlayerName();
		ServerSetPlayerNameFromGameInstance(name);

		if (!name.IsEmpty()) SetPlayerName(name);
		else SetPlayerName(FString::Printf(TEXT("Player %d"), GetPlayerIndex()));
	}
}

void AGnirutPlayerState::ServerSetPlayerNameFromGameInstance_Implementation(const FString& PlayerName)
{
	SetPlayerNameAndUpdate(PlayerName);
}

void AGnirutPlayerState::SetPlayerNameAndUpdate(const FString& PlayerName)
{
	if (!PlayerName.IsEmpty()) SetPlayerName(PlayerName);
	else SetPlayerName(FString::Printf(TEXT("Player %d"), GetPlayerIndex()));	

	UWorld* world = GetWorld();
	if (world)
	{
		AGnirutGameMode* GGM = Cast<AGnirutGameMode>(world->GetAuthGameMode());
		if (GGM)
		{
			GGM->UpdatePlayerList();
		}
	}
}

void AGnirutPlayerState::SetPlayerIndex(int32 NewIndex)
{
	PlayerIndex = NewIndex;
}

void AGnirutPlayerState::SetDead()
{
	ServerSetDead();
}

void AGnirutPlayerState::ServerSetDead_Implementation()
{
	bIsAlive = false;
	UpdatePlayerAlive();
}

void AGnirutPlayerState::OnRep_SetDead()
{
	UpdatePlayerAlive();
}

void AGnirutPlayerState::SetHoldingItem(bool IsHoldingItem)
{
	ServerSetHoldingItem(IsHoldingItem);
}

void AGnirutPlayerState::ServerSetHoldingItem_Implementation(bool IsHoldingItem)
{
	bIsHoldingItem = IsHoldingItem;
}

void AGnirutPlayerState::UpdatePlayerAlive()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UGnirutPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UGnirutPlayerList* GPL = Cast<UGnirutPlayerList>(UW);
			if (GPL)
			{
				GPL->UpdatePlayerAlive(GetPlayerId(), bIsAlive);
			}
		}
	}
}

void AGnirutPlayerState::OnRep_Kills()
{
	UpdateKills();
}

void AGnirutPlayerState::UpdateKills()
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UGnirutPlayerList::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UGnirutPlayerList* GPL = Cast<UGnirutPlayerList>(UW);
			if (GPL)
			{
				GPL->UpdateKills(GetPlayerId(), HumanPlayerKills, AIPlayerKills);
			}
		}
	}
}

void AGnirutPlayerState::SetKillLogHUD(const FString& Content)
{
	ServerSetKillLogHUD(Content);
}

void AGnirutPlayerState::ServerSetKillLogHUD_Implementation(const FString& Content)
{
	MulticastSetKillLogHUD(Content);
}

void AGnirutPlayerState::MulticastSetKillLogHUD_Implementation(const FString& Content)
{
	UWorld* world = GetWorld();
	if (world)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(world, FoundWidgets, UKillLogHUD::StaticClass(), false);

		for (UUserWidget* UW : FoundWidgets)
		{
			UKillLogHUD* UKL = Cast<UKillLogHUD>(UW);
			if (UKL)
			{
				UKL->SetKillLogTextBlock(Content);
			}
		}
	}
}

void AGnirutPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGnirutPlayerState, bIsAlive);
	DOREPLIFETIME(AGnirutPlayerState, AIPlayerKills);
	DOREPLIFETIME(AGnirutPlayerState, HumanPlayerKills);
	DOREPLIFETIME(AGnirutPlayerState, PlayerIndex);
}
