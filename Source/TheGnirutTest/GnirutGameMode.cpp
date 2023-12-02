// Copyright Epic Games, Inc. All Rights Reserved.

#include "GnirutGameMode.h"
#include "GnirutCharacter.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GnirutHumanPlayer.h"
#include "GnirutPlayerController.h"
#include "GnirutGameInstance.h"

AGnirutGameMode::AGnirutGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Gnirut/BP_GnirutHumanPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Gnirut/BP_GnirutPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	GameStateClass = AGnirutGameState::StaticClass();
	PlayerStateClass = AGnirutPlayerState::StaticClass();
}

int32 AGnirutGameMode::GetCurrentPlayerCount()
{
	return GetNumPlayers();
}

void AGnirutGameMode::StartPlay()
{
	Super::StartPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("AI"), Actors);
	AGnirutGameState* GnirutGameState = GetGameState<AGnirutGameState>();
	GnirutGameState->InitPlayerCounts_Implementation(Actors.Num() - 1, GetCurrentPlayerCount());
}

void AGnirutGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AGnirutGameState* GnirutGameState = GetGameState<AGnirutGameState>();
	GnirutGameState->PlayerLogin_Implementation();

	AGnirutPlayerState* GnirutPlayerState = Cast<AGnirutPlayerState>(NewPlayer->PlayerState);
	if (GnirutPlayerState)
	{
		GnirutPlayerState->SetPlayerIndex(GnirutGameState->GetNumberOfHumanPlayers());
		FString NewNickName = FString::Printf(TEXT("Player %d"), GnirutPlayerState->GetPlayerIndex());
		UGnirutGameInstance* GGI = Cast<UGnirutGameInstance>(GetGameInstance());
		if (GGI)
		{
			if (NewPlayer->IsLocalPlayerController() && !GGI->GetPlayerName().IsEmpty()) {
				NewNickName = GGI->GetPlayerName();
			}
			else if (NewPlayer->GetNetConnection())
			{
				uint32 key = NewPlayer->GetNetConnection()->GetConnectionId();
				//UE_LOG(LogTemp, Display, TEXT("%s"), *(NewPlayer->GetNetConnection()->LowLevelGetRemoteAddress()));
				//UE_LOG(LogTemp, Display, TEXT("%d"), NewPlayer->GetNetConnection()->GetConnectionId());
				GGI->PlayerNameMap.RemoveAndCopyValue(key, NewNickName);
			}
		}
		GnirutPlayerState->SetPlayerNickName(NewNickName);
	}
	UpdatePlayerList();
}

void AGnirutGameMode::Logout(AController* Exiting)
{

	AGnirutPlayerController* GPC = Cast<AGnirutPlayerController>(Exiting);
	if (GPC)
	{
		// delay to call UpdatePlayerList after PlayerArray being updated;
		FTimerHandle LogoutTimer;
		GetWorldTimerManager().SetTimer(
			LogoutTimer,
			this,
			&AGnirutGameMode::UpdatePlayerList,
			0.3f
		);
	}

	Super::Logout(Exiting);
}


void AGnirutGameMode::UpdatePlayerList()
{
	AGnirutGameState* GGS = Cast<AGnirutGameState>(GameState);
	if (GGS)
	{
		GGS->UpdateAllPlayerStates();
	}
}