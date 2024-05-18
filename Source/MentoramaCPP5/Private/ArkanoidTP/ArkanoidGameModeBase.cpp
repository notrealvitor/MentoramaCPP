// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/ArkanoidGameModeBase.h"

#include "ArkanoidTP/ArkanoidPlayerState.h"
#include "ArkanoidTP/ArkanoidPlayerController.h"
#include "ArkanoidTP/BrickManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "MentoramaHelpers.h"
#include "Kismet/GameplayStatics.h"


AArkanoidGameModeBase::AArkanoidGameModeBase() : Super()
{
	//this sets the BP_BrickManager as the BrickManager class, in this case I like in blueprint more but it is good for reference when needed
	static ConstructorHelpers::FClassFinder<AActor> ActorBPClass(TEXT("/Game/ThirdPersonArkanoid/Bricks/BP_BrickManager"));
	if (ActorBPClass.Succeeded())
	{
		BrickManagerClass = ActorBPClass.Class;
	}
}

void AArkanoidGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnBrickManager();
	//StartRound(CurrentRound);
}


void AArkanoidGameModeBase::EndRound() //This happens on AllBricksDestroyed
{
	//when the round ends
	//CurrentRound++; // I like this more being controlled by the widget, this way the player can retry
}

void AArkanoidGameModeBase::StartRound(int Round, int NRows, int NColumns, int BrickHealth)
{
	auto* PlayerController = Cast<AArkanoidPlayerController>(GetWorld()->GetFirstPlayerController());
	check(PlayerController);
	OnRoundStart.Broadcast(Round);

	//PlayerController->DeleteAllBalls();
	BrickManager->SpawnBricks(NRows,NColumns,BrickHealth);
}

void AArkanoidGameModeBase::SpawnBrickManager()
{
	if (GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//BrickManager = CreateDefaultSubobject<ABrickManager>(TEXT("BrickManager")); //this could be removed but I will leave for education reasons
		BrickManager = GetWorld()->SpawnActor<ABrickManager>(BrickManagerClass.Get(), SpawnLocation, FRotator(0.0f,0.0f,0.0f),SpawnParams);
		BrickManager->OnAllBricksDestroyed.AddDynamic(this, &AArkanoidGameModeBase::EndRound);
	}
}



