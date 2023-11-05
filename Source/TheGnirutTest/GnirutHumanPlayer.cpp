// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutHumanPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GnirutAnimInstance.h"
#include "DrawDebugHelpers.h"

AGnirutHumanPlayer::AGnirutHumanPlayer()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	IsAttacking = false;
	AttackRange = 60.0f;
	AttackRadius = 50.0f;
}

void AGnirutHumanPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AGnirutHumanPlayer::OnAttackMontageEnded);
		AnimInstance->OnAttackHitCheck.AddUObject(this, &AGnirutHumanPlayer::AttackCheck);
	}
}

void AGnirutHumanPlayer::BeginPlay()
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

void AGnirutHumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGnirutHumanPlayer::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGnirutHumanPlayer::Look);

		// Running
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AGnirutHumanPlayer::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AGnirutHumanPlayer::StopRunning);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGnirutHumanPlayer::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGnirutHumanPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGnirutHumanPlayer::Look(const FInputActionValue& Value)
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

void AGnirutHumanPlayer::Run(const FInputActionValue& Value)
{
	ServerRun();
}

void AGnirutHumanPlayer::ServerRun_Implementation()
{
	MulticastRun();
}

void AGnirutHumanPlayer::MulticastRun_Implementation()
{
	if (Controller != nullptr) {
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AGnirutHumanPlayer::StopRunning(const FInputActionValue& Value)
{
	ServerStopRunning();
}

void AGnirutHumanPlayer::ServerStopRunning_Implementation()
{
	MulticastStopRunning();
}

void AGnirutHumanPlayer::MulticastStopRunning_Implementation() 
{
	if (Controller != nullptr) {
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
}

void AGnirutHumanPlayer::Attack()
{
	ServerAttack();
}

void AGnirutHumanPlayer::ServerAttack_Implementation()
{
	MulticastAttack();
}

void AGnirutHumanPlayer::MulticastAttack_Implementation()
{
	if (!IsAttacking) {
		AnimInstance->PlayAttackMontage();
		IsAttacking = true;
	}
}

void AGnirutHumanPlayer::AttackCheck()
{
	if (!HasAuthority()) return;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule
	(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
#endif

	if (bResult)
	{
		if (HitResult.GetActor())
		{
			ATheGnirutTestCharacter* TargetCharacter = Cast<ATheGnirutTestCharacter>(HitResult.GetActor());
			if (TargetCharacter)
			{
				TargetCharacter->Dying();
			}
		}
	}
}

void AGnirutHumanPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
