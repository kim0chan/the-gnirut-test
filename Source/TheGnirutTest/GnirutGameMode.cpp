// Copyright Epic Games, Inc. All Rights Reserved.

#include "GnirutGameMode.h"
#include "GnirutCharacter.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GnirutHumanPlayer.h"
#include "GnirutPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Math/UnrealMathUtility.h"

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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	NumPlayerStarts = PlayerStarts.Num();

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
		GnirutPlayerState->InitPlayerName();
	}
	UpdatePlayerList();
}

void AGnirutGameMode::Logout(AController* Exiting)
{
	AGnirutPlayerState* GPS = Exiting->GetPlayerState<AGnirutPlayerState>();
	if (GPS && GPS->GetIsAlive())
	{
		AGnirutGameState* GnirutGameState = GetGameState<AGnirutGameState>();
		GnirutGameState->PlayerLogout_Implementation();
	}

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

AActor* AGnirutGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (NumPlayerStarts > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, NumPlayerStarts - 1);
		AActor* ChosenPlayerStart = PlayerStarts[RandomIndex];
		PlayerStarts.RemoveAt(RandomIndex);
		NumPlayerStarts--;
		return ChosenPlayerStart;
	}
	else
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
}
