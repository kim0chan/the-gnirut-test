// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutAnimInstance.h"
#include "TheGnirutTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UGnirutAnimInstance::UGnirutAnimInstance()
{
	Character = nullptr;
	MovementComponent = nullptr;

	Velocity = {};
	GroundSpeed = 0.0f;
	IsFalling = false;
	ShouldMove = false;
}

void UGnirutAnimInstance::NativeInitializeAnimation()
{
	auto Actor = GetOwningActor();
	Character = Cast<ATheGnirutTestCharacter>(Actor);
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UGnirutAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(Character))
	{
		Velocity = MovementComponent->Velocity;
		GroundSpeed = Velocity.Size2D();
		ShouldMove = MovementComponent->GetCurrentAcceleration() != FVector(0, 0, 0) && GroundSpeed > 3.0;
		IsFalling = MovementComponent->IsFalling();		
	}
}

