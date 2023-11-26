// Fill out your copyright notice in the Description page of Project Settings.


#include "GnirutAnimInstance.h"
#include "GnirutCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UGnirutAnimInstance::UGnirutAnimInstance()
{
	Character = nullptr;
	MovementComponent = nullptr;

	Velocity = {};
	GroundSpeed = 0.0f;
	IsFalling = false;
	ShouldMove = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder <UAnimMontage> ANIM_MONTAGE
	(TEXT("/Game/Characters/Mannequins/Animations/AM_GnirutCharacter.AM_GnirutCharacter"));

	if (ANIM_MONTAGE.Succeeded())
		AnimMontage = ANIM_MONTAGE.Object;
}

void UGnirutAnimInstance::NativeInitializeAnimation()
{
	auto Actor = GetOwningActor();
	Character = Cast<AGnirutCharacter>(Actor);
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

void UGnirutAnimInstance::PlayAttackMontage()
{
	Montage_Play(AnimMontage, 1.5f);
}

void UGnirutAnimInstance::SetDead()
{
	IsDead = true;
}

void UGnirutAnimInstance::AnimNotify_AttackHitCheck()
{
	// Broadcast - run all function in delegate
	OnAttackHitCheck.Broadcast();
}

