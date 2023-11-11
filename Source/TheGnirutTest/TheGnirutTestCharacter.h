// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TheGnirutTestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATheGnirutTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATheGnirutTestCharacter();

	UFUNCTION(NetMulticast, Reliable)
	virtual void Dying();

protected:
	const float WalkingSpeed = 250.0f;
	const float RunningSpeed = 500.0f;

	UPROPERTY()
	class UGnirutAnimInstance* AnimInstance;

protected:

	virtual void PostInitializeComponents() override;

};

