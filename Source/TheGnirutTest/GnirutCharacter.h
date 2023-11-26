// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GnirutCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AGnirutCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGnirutCharacter();
	
	UFUNCTION()
	virtual void Dying();

	UFUNCTION(Server, Reliable)
	virtual void ServerDying();
	virtual void ServerDying_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastDying();
	virtual void MulticastDying_Implementation();

protected:
	const float WalkingSpeed = 250.0f;
	const float RunningSpeed = 500.0f;

	UPROPERTY()
	class UGnirutAnimInstance* AnimInstance;
	virtual void PostInitializeComponents() override;
};
