// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGnirutTestGameMode.h"
#include "TheGnirutTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheGnirutTestGameMode::ATheGnirutTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_GnirutHumanPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_GnirutPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ATheGnirutTestGameMode::DecrementAliveGnirutHumanPlayers()
{
	NumAliveGnirutHumanPlayers--;
	CheckGameEnd();
}

void ATheGnirutTestGameMode::CheckGameEnd()
{
	UE_LOG(LogTemp, Display, TEXT("%d"), NumAliveGnirutHumanPlayers);
	if (NumAliveGnirutHumanPlayers <= 1)
	{
		UE_LOG(LogTemp, Display, TEXT("GAME END!"));
	}

}