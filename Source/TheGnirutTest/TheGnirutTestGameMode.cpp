// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGnirutTestGameMode.h"
#include "TheGnirutTestCharacter.h"
#include "TheGnirutTestGameState.h"
#include "GnirutPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GnirutHumanPlayer.h"
#include "AGnirutPlayerController.h"

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

	//if (NewPlayer->GetNetConnection()) {
	//	UE_LOG(LogTemp, Display, TEXT("** %d"), NewPlayer->GetNetConnection()->GetConnectionId());
	//}

	UpdatePlayerList();
}

void ATheGnirutTestGameMode::Logout(AController* Exiting)
{

	AAGnirutPlayerController* GPC = Cast<AAGnirutPlayerController>(Exiting);
	if (GPC)
	{
		// delay to call UpdatePlayerList after PlayerArray being updated;
		FTimerHandle LogoutTimer;
		GetWorldTimerManager().SetTimer(
			LogoutTimer,
			this,
			&ATheGnirutTestGameMode::UpdatePlayerList,
			0.3f
		);
	}

	Super::Logout(Exiting);
}


void ATheGnirutTestGameMode::UpdatePlayerList()
{
	ATheGnirutTestGameState* GGS = Cast<ATheGnirutTestGameState>(GameState);
	if (GGS)
	{
		GGS->UpdateAllPlayerStates();
	}
}