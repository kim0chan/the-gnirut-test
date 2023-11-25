// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGnirutTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GnirutAnimInstance.h"
#include "GnirutHumanPlayer.h"
#include "TheGnirutTestGameMode.h"
#include "TheGnirutTestGameState.h"
#include "GnirutPlayerState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheGnirutTestCharacter

ATheGnirutTestCharacter::ATheGnirutTestCharacter()
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

void ATheGnirutTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UGnirutAnimInstance>(GetMesh()->GetAnimInstance());
}

void ATheGnirutTestCharacter::Dying()
{
	AController* CharacterController = GetController();
	if (CharacterController)
	{
		CharacterController->UnPossess();
	}
	// TODO: need to fix Bug. 
	// If enable the following line, the Character fall through the floor...
	//SetActorEnableCollision(false);
	ServerDying();
}

void ATheGnirutTestCharacter::ServerDying_Implementation()
{
	MulticastDying();
}

void ATheGnirutTestCharacter::MulticastDying_Implementation()
{
	AnimInstance->SetDead();
	GetCapsuleComponent()->DestroyComponent();
	if (!HasAuthority())	return;
	AGnirutHumanPlayer* HumanPlayer = Cast<AGnirutHumanPlayer>(this);
	ATheGnirutTestGameState* GnirutGameState = GetWorld()->GetGameState<ATheGnirutTestGameState>();
	if (!GnirutGameState)	return;
	GnirutGameState->DecrementPlayerCounts_Implementation(!HumanPlayer);
}
