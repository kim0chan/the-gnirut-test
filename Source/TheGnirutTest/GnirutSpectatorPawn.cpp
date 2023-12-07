// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutSpectatorPawn.h"
#include "GnirutPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AGnirutSpectatorPawn::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGnirutSpectatorPawn::MoveUp()
{
	if (Controller != nullptr)
	{
		AddMovementInput(FVector::UpVector, 1.0f);
	}
}

void AGnirutSpectatorPawn::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGnirutSpectatorPawn::PressTab()
{
	AGnirutPlayerController* GPC = Cast<AGnirutPlayerController>(Controller);
	if (GPC)
	{
		GPC->ToggleTabMenuVisibility();
	}
}

void AGnirutSpectatorPawn::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGnirutSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		//// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Ongoing, this, &ThisClass::MoveUp);

		//// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		// Tab Menu toggle
		EnhancedInputComponent->BindAction(TabkeyAction, ETriggerEvent::Started, this, &ThisClass::PressTab);
	}
}
