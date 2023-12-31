// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GnirutCharacter.h"
#include "ObjectiveItem.h"
#include "GnirutHumanPlayer.generated.h"

/**
 *
 */
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class THEGNIRUTTEST_API AGnirutHumanPlayer : public AGnirutCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Run Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	/** Attack Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Interact Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Tabkey Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TabkeyAction;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGnirutSpectatorPawn> SpectatorPawnClass;


public:
	AGnirutHumanPlayer();

	UPROPERTY(Replicated)
	AObjectiveItem* HoldingItem;

	UFUNCTION()
	void SetHoldingItem(AObjectiveItem* Item);

	void DropItem();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Run(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerRun();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRun();

	UFUNCTION()
	void StopRunning(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerStopRunning();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopRunning();

	UFUNCTION()
	void Attack();

	UFUNCTION(Server, Reliable)
	void ServerAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack();

	UFUNCTION()
	void AttackCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	//UPROPERTY()
	//class UGnirutAnimInstance* AnimInstance;

	void Interact();

	UFUNCTION(Server, Reliable)
	void ServerInteract(FVector Start, FVector End);
	void ServerInteract_Implementation(FVector Start, FVector End);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastInteract(FVector Start, FVector End);
	void MulticastInteract_Implementation(FVector Start, FVector End);

	UFUNCTION(Server, Reliable)
	void ServerDropItem(FVector DropLocation);
	void ServerDropItem_Implementation(FVector DropLocation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDropItem(FVector DropLocation);
	void MulticastDropItem_Implementation(FVector DropLocation);

	//UFUNCTION(Server, Reliable)
	//void ServerDropItem();
	//void ServerDropItem_Implementation();

	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastDropItem();
	//void MulticastDropItem_Implementation();

	UFUNCTION()
	void PressTab();

	virtual void PostInitializeComponents() override;

	// To add mapping context
	virtual void BeginPlay();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Dying(class AGnirutPlayerState* Attacker) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
