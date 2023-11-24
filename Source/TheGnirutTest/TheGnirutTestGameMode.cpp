// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGnirutTestGameMode.h"
#include "TheGnirutTestCharacter.h"
#include "TheGnirutTestGameState.h"
#include "GnirutPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GnirutHumanPlayer.h"

ATheGnirutTestGameMode::ATheGnirutTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_GnirutHumanPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_AGnirutPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	GameStateClass = ATheGnirutTestGameState::StaticClass();
	PlayerStateClass = AGnirutPlayerState::StaticClass();
}

int32 ATheGnirutTestGameMode::GetCurrentPlayerCount()
{
	return GetNumPlayers();
}

void ATheGnirutTestGameMode::StartPlay()
{
	Super::StartPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("AI"), Actors);
	ATheGnirutTestGameState* GnirutGameState = GetGameState<ATheGnirutTestGameState>();
	GnirutGameState->InitPlayerCounts_Implementation(Actors.Num() - 1, GetCurrentPlayerCount());
}

void ATheGnirutTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ATheGnirutTestGameState* GnirutGameState = GetGameState<ATheGnirutTestGameState>();
	GnirutGameState->PlayerLogin_Implementation();

	AGnirutPlayerState* GnirutPlayerState = Cast<AGnirutPlayerState>(NewPlayer->PlayerState);
	if (GnirutPlayerState)
	{
		GnirutPlayerState->SetPlayerIndex(GnirutGameState->GetNumberOfHumanPlayers());
		FString NewNickName = FString::Printf(TEXT("Player %d"), GnirutPlayerState->GetPlayerIndex());
		GnirutPlayerState->SetPlayerNickName(NewNickName);
	}
}
