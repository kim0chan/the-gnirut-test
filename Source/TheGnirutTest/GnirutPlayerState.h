// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GnirutPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THEGNIRUTTEST_API AGnirutPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AGnirutPlayerState();

	int32 GetAIPlayerKills() const;
	int32 GetHumanPlayerKills() const;
	int32 GetTotalPlayerKills() const;
	int32 GetPlayerIndex() const;
	FString GetPlayerNickName()	const;
	bool GetIsAlive() const;

	void AddAIPlayerKills();
	void AddHumanPlayerKills();
	void SetPlayerNickName(const FString& NewNickName);
	void SetPlayerIndex(int32 NewIndex);
	void SetKillLogHUD(const FString& Content);

	void SetDead();
	UFUNCTION(Server, Unreliable)
	void ServerSetDead();
	UFUNCTION()
	void OnRep_SetDead();
	void UpdatePlayerAlive();

	UFUNCTION()
	void OnRep_Kills();
	void UpdateKills();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_SetDead, BlueprintReadOnly, Category = "PlayerState")
	bool bIsAlive;

	UPROPERTY(ReplicatedUsing = OnRep_Kills, BlueprintReadOnly, Category = "PlayerState")
	int32 AIPlayerKills;

	UPROPERTY(ReplicatedUsing = OnRep_Kills, BlueprintReadOnly, Category = "PlayerState")
	int32 HumanPlayerKills;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	int32 PlayerIndex;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	FString PlayerNickName;

	UFUNCTION(Server, Reliable)
	void ServerSetKillLogHUD(const FString& Content);
	void ServerSetKillLogHUD_Implementation(const FString& Content);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetKillLogHUD(const FString& Content);
	void MulticastSetKillLogHUD_Implementation(const FString& Content);
};
