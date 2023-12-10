// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GnirutSpectatorPawn.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AGnirutSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Tabkey Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TabkeyAction;

public:
	void SetDefaultMappingContext();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for movement input */
	void MoveUp();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void PressTab();

	// To add mapping context
	virtual void BeginPlay();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
