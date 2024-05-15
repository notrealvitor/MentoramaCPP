// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/BrickManager.h"

#include "ArkanoidTP/ArkanoidGameModeBase.h"
#include "Logging/StructuredLog.h"
#include "ArkanoidTP/Brick.h"
#include "ArkanoidTP/ArkanoidPlayerState.h"


ABrickManager::ABrickManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABrickManager::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &ABrickManager::CheckBricks, 1.0f, true, 2.0f); //this will call the CheckBricks function every 1second
}

FVector ABrickManager::GetPositionFor(int y, int z)
{
	FVector position = StartSpawnPosition = GetActorLocation();
	position.Y += y * BrickExtend.Y * 2;
	position.Y += y * OffsetBetweenBricks.Y * 2;
	position.Z += z * -BrickExtend.Z * 2;									//added the - sign so the bricks are created down
	position.Z += z * -OffsetBetweenBricks.Z * 2;							//added the - sign so the bricks are created down
	return position;
}

void ABrickManager::SpawnBricks(int  NumRows = 2, int NumColumns = 10, int BrickHealth = 2)
{
	for(int z=0; z < NumColumns; z++)
	{
		for(int y=0; y < NumRows; y++)
		{
			auto* brick = GetWorld()->SpawnActor<ABrick>(BrickClass.Get());
			if(BrickExtend.IsZero())
			{
				FVector origin;
				brick->GetActorBounds(true, origin, BrickExtend);
			}
			brick->SetActorLocation(GetPositionFor(y,z));
			brick->OnBrickDestroyed.AddDynamic(this, &ABrickManager::HandleBrickDestroyed);
			brick->Health = BrickHealth;
			Bricks.Add(brick);
		}
	}
}

void ABrickManager::HandleBrickDestroyed(ABrick* DestroyedBrick)
{
	ApplyScore(DestroyedBrick);
	Bricks.Remove(DestroyedBrick);
	if (Bricks.Num() <= 0)
	{
		OnAllBricksDestroyed.Broadcast();
	}
}

void ABrickManager::ApplyScore(ABrick* DestroyedBrick)
{
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(playerController)) return;
	APlayerState* playerState = playerController->PlayerState;			//this wasnt building with auto*
	if(!IsValid(playerState)) return;
	playerState->SetScore(playerState->GetScore() + DestroyedBrick->GetScoreValue());
}







