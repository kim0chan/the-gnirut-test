// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGnirutTestGameMode.h"
#include "TheGnirutTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheGnirutTestGameMode::ATheGnirutTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}