// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/ArkanoidPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MentoramaCPP5Character.h"

DEFINE_LOG_CATEGORY(LogArkanoidCharacter);

void AArkanoidPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HoldingBall)
	{
		HoldingBall->SetActorLocation(GetPawn()->GetActorLocation() + OffsetSpawnInitialBall);
	}
}

void AArkanoidPlayerController::BeginPlay()
{
	Super::BeginPlay();
	EnableLaunch();
}

ABall* AArkanoidPlayerController::SpawnBall()
{
	auto* ball = GetWorld()->SpawnActor<ABall>(BallClass.Get());
	return ball;
}

void AArkanoidPlayerController::EnableLaunch()
{
	HoldingBall = SpawnBall();
	OnEnableLaunch.Broadcast();
	if(HoldingBall && GetPawn() ) //check if those are valid
	{
		HoldingBall->SetActorLocation(GetPawn()->GetActorLocation() + OffsetSpawnInitialBall);
	}
}

void AArkanoidPlayerController::DisableLaunch()
{
	HoldingBall = NULL;
	OnDisableLaunch.Broadcast();
}

void AArkanoidPlayerController::LaunchHoldingBall()
{
	if(HoldingBall)
	{
		HoldingBall->Launch();
		DisableLaunch();
	}
}

