#include "ArkanoidTP/ArkanoidPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MentoramaCPP5Character.h"
#include "ArkanoidTP/ArkanoidPlayerState.h"

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
	Balls.Add(ball);
	ball->OnBallDestroyed.AddDynamic(this, &AArkanoidPlayerController::OnBallDestroyed);
	return ball;
}

void AArkanoidPlayerController::DestroyBall(ABall* Ball)
{
	GetPlayerState<AArkanoidPlayerState>()->Lives--;
	EventBallDestroyed(); //this a workaround to pass the Lives value to the VM which is not in CPP yet
	Ball->DestroyBall();
	if (GetPlayerState<AArkanoidPlayerState>()->Lives)
	{
		EnableLaunch();
	}
	else
	{
		OnEndGame.Broadcast();
	}
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

void AArkanoidPlayerController::DestroyAllBalls()
{
	for (auto* ball : Balls)
	{
		if (ball)
		{
			ball->Destroy();
		}		
	}
	Balls.Reset();
}

void AArkanoidPlayerController::OnBallDestroyed(ABall* ball)
{
	Balls.Remove(ball);
	if (Balls.Num() <= 0)
	{
		//endround
	}
}



