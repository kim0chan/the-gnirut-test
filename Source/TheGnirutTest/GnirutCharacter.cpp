// Copyright Epic Games, Inc. All Rights Reserved.

#include "GnirutCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpectatorPawn.h"
#include "GnirutAnimInstance.h"
#include "GnirutHumanPlayer.h"
#include "GnirutGameMode.h"
#include "GnirutGameState.h"
#include "GnirutPlayerState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheGnirutTestCharacter

AGnirutCharacter::AGnirutCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.75f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("GnirutCharacter"));
}

void AGnirutCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UGnirutAnimInstance>(GetMesh()->GetAnimInstance());
}

void AGnirutCharacter::Dying()
{
	AGnirutPlayerState* GPS = Cast<AGnirutPlayerState>(GetPlayerState());
	if (GPS)
	{
		GPS->SetDead();
	}

	ServerDying();

	AController* CharacterController = GetController();
	if (CharacterController)
	{
		CharacterController->UnPossess();
	}
}

void AGnirutCharacter::ServerDying_Implementation()
{
	AGnirutHumanPlayer* HumanPlayer = Cast<AGnirutHumanPlayer>(this);
	AGnirutGameState* GnirutGameState = GetWorld()->GetGameState<AGnirutGameState>();
	if (!GnirutGameState)	return;
	GnirutGameState->DecrementPlayerCounts_Implementation(!HumanPlayer);
	MulticastDying();
}

void AGnirutCharacter::MulticastDying_Implementation()
{
	AnimInstance->SetDead();
	GetCapsuleComponent()->DestroyComponent();
}
