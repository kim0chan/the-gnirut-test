// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveItem.h"
#include "Net/UnrealNetwork.h"
#include "GnirutHumanPlayer.h"
#include "ItemHUD.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GnirutGameState.h"

AObjectiveItem::AObjectiveItem()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	RootComponent = BoxMesh;

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ItemWidget"));
	ItemWidget->SetupAttachment(BoxMesh);
	//ItemWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	ItemWidget->SetWidgetSpace(EWidgetSpace::Screen);

	OccupyingPlayer = nullptr;
	IsOccupied = false;
	HeightOffset = 50.0f;
	bReplicates = true;
	RemainingTime = 40.0f;
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
	if (!HasAuthority() || RemainingTime <= 0.0f)	return;
	if (IsOccupied)
	{
		RemainingTime -= DeltaTime;

		ServerUpdateRemainingTime(RemainingTime);

		if (RemainingTime <= 0.0f)
		{
			AGnirutGameState* GnirutGameState = GetWorld()->GetGameState<AGnirutGameState>();
			if (GnirutGameState)
			{
				GnirutGameState->CheckGameEndByItem_Implementation();
			}

			RemainingTime = 0.0f;
		}
	}
}

void AObjectiveItem::ServerUpdateRemainingTime_Implementation(float Time)
{
	MulticastUpdateRemainingTime(Time);
}

void AObjectiveItem::MulticastUpdateRemainingTime_Implementation(float Time)
{
	UItemHUD* IW = Cast<UItemHUD>(ItemWidget->GetUserWidgetObject());
	if (IW)
	{
		IW->UpdateTextBlock(FString::Printf(TEXT("%.1fs"), Time));
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
		UpdateRemainingTime(DeltaTime);

		FVector NewLocation = OccupyingPlayer->GetActorLocation() + FVector(0, 0, HeightOffset);
		FRotator NewRotation = OccupyingPlayer->GetActorRotation();

		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}
