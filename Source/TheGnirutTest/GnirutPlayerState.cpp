// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "KillLogHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AGnirutPlayerState::AGnirutPlayerState()
{
	AIPlayerKills = 0;
	HumanPlayerKills = 0;
	PlayerIndex = 0;
	SetPlayerNickName("Placeholder");
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

FString AGnirutPlayerState::GetPlayerNickName() const
{
	return PlayerNickName;
}

void AGnirutPlayerState::AddAIPlayerKills()
{
	++AIPlayerKills;
	UE_LOG(LogTemp, Warning, TEXT("[Player %s] Killed %d AI(s)."), *GetPlayerNickName(), GetAIPlayerKills());
}

void AGnirutPlayerState::AddHumanPlayerKills()
{
	++HumanPlayerKills;
	UE_LOG(LogTemp, Warning, TEXT("[Player %s] Killed %d Human(s)."), *GetPlayerNickName(), GetHumanPlayerKills());
}

void AGnirutPlayerState::SetPlayerNickName(const FString& NewNickName)
{
	PlayerNickName = NewNickName;
}

void AGnirutPlayerState::SetPlayerIndex(int32 NewIndex)
{
	PlayerIndex = NewIndex;
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

	DOREPLIFETIME(AGnirutPlayerState, AIPlayerKills);
	DOREPLIFETIME(AGnirutPlayerState, HumanPlayerKills);
	DOREPLIFETIME(AGnirutPlayerState, PlayerIndex);
	DOREPLIFETIME(AGnirutPlayerState, PlayerNickName);
}
