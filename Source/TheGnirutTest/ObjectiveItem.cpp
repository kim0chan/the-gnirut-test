// Fill out your copyright notice in the Description page of Project Settings.


#include "Net/UnrealNetwork.h"
#include "ObjectiveItem.h"
#include "GnirutHumanPlayer.h"
#include "Components/StaticMeshComponent.h"

AObjectiveItem::AObjectiveItem()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;
	OccupyingPlayer = nullptr;
	IsOccupied = false;
	HeightOffset = 50.0f;
	bReplicates = true;
	RemainingTime = 25.0f;
	DisplayText = FString("0");
}

void AObjectiveItem::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectiveItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AObjectiveItem, OccupyingPlayer, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AObjectiveItem, IsOccupied, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AObjectiveItem, RemainingTime, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AObjectiveItem, DisplayText, COND_OwnerOnly);

}

void AObjectiveItem::OccupyItem(class AGnirutHumanPlayer* Player)
{
	if (IsOccupied)		return;
	if (Player)
	{
		//SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		OccupyingPlayer = Player;
		Player->SetHoldingItem(this);
		IsOccupied = true;
	}
}

void AObjectiveItem::UnOccupyItem()
{
	if (!IsOccupied)		return;
	IsOccupied = false;
	SetActorEnableCollision(true);
}

void AObjectiveItem::UpdateRemainingTime(float DeltaTime)
{
	if (IsOccupied)
	{
		RemainingTime -= DeltaTime;

		if (RemainingTime <= 0.0f)
		{
			// GAME OVER BY HOLDING ITEM.
			RemainingTime = 0.0f;
		}
	}
}


void AObjectiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsOccupied)
	{
		FRotator NewRotation = GetActorRotation() + FRotator(0, 200.0f * DeltaTime, 0);
		SetActorRotation(NewRotation);
	}
	else
	{
		if (HasAuthority())
		{
			UpdateRemainingTime(DeltaTime);
		}

		FVector NewLocation = OccupyingPlayer->GetActorLocation() + FVector(0, 0, HeightOffset);
		FRotator NewRotation = OccupyingPlayer->GetActorRotation();

		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

void AObjectiveItem::OnRep_RemainingTime()
{
	DisplayText = FString::Printf(TEXT("%.1f"), RemainingTime);
}

void AObjectiveItem::DrawHUD(APlayerController* PC, UCanvas* Canvas, FVector2D ViewportSize)
{
	if (Canvas && PC)
	{
		FVector2D ScreenPosition;

		PC->ProjectWorldLocationToScreen(GetActorLocation(), ScreenPosition);
		//Canvas->DrawText(FVector2D(ScreenPosition.X, ScreenPosition.Y - 20), FText::FromString(DisplayText), GEngine->GetSmallFont(), FLinearColor::Red);
	}
}
