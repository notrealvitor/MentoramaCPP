#include "ArkanoidTP/ArkanoidPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MentoramaCPP5Character.h"
#include "MentoramaGameInstance.h"
#include "Logging/StructuredLog.h"

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

	//Gets the Visual Model from the Game Instance
	MyMentoramaGameInstance = Cast<UMentoramaGameInstance>(GetGameInstance());
	
	if (MyMentoramaGameInstance)
	{
		VM_NotPlayerProperties = MyMentoramaGameInstance->VM_NotPlayerProperties;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("VM_NotPlayerProperties not found!"));
	}
}

ABall* AArkanoidPlayerController::SpawnBall()
{
	auto* ball = GetWorld()->SpawnActor<ABall>(BallClass.Get());
	ball->BallDamage = SpawnBallDamage;
	Balls.Add(ball);
	return ball;
}

void AArkanoidPlayerController::DestroyBall(ABall* Ball)
{
	Balls.Remove(Ball);
	Ball->DestroyBall();
	if (VM_NotPlayerProperties)
	{
		VM_NotPlayerProperties->SetFailContext(VM_NotPlayerProperties->FailContext - 1.0f);
		UE_LOGFMT(LogTemp, Log, "REMAINING LIVES {1}", VM_NotPlayerProperties->FailContext);
		if (VM_NotPlayerProperties->FailContext >= 0)
		{
			if (Balls.Num() <= 0) //make sure there are no extra balls reamining
			{
				EnableLaunch();
			}
		}
		else
		{
			OnEndGame.Broadcast();
		}
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