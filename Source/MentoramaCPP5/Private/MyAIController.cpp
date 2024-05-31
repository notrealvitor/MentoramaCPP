// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
// Fill out your copyright notice in the Description page of Project Settings.
#include "AI_Character.h"
#include "GameFramework/Controller.h"

// Sets default values
AMyAIController::AMyAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	StartingPoint =  AController::GetPawn()->GetActorLocation();
}

void AMyAIController::MoveToPoint(FVector MovingPoint)
{
	if (PatrolIsMoving == false)
	{
		MoveToLocation((MovingPoint), 100, false );
	//	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Moving to Point %s"), *MovingPoint.ToString() ), true, true, FColor::Green, 5);
		PatrolIsMoving=true;
	}
	else
	{
	//	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("NOT MOVING") ), true, true, FColor::Green, 0);
	}
	//MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AMyAIController::LookToPoint(FVector LookingPoint)
{
	AController::GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->K2_GetActorLocation(), LookingPoint));
}

void AMyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result); 
	PatrolIsMoving = false;
	if (PatrolIsReturning == false)
	{
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ReturningPatrol") ), true, true, FColor::Green, 5); DEBUG
		PatrolIsReturning = true;
	}
	else
	{
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("GoingPatrol") ), true, true, FColor::Green, 5); DEBUG
		PatrolIsReturning = false;
	}

	Cast<AAI_Character>(GetPawn())->TimePassed = 0;
	
}

