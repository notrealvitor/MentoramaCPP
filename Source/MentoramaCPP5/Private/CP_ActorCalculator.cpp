// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_ActorCalculator.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACP_ActorCalculator::ACP_ActorCalculator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

Calculations::Calculations() 
{ 
}

// Called when the game starts or when spawned
void ACP_ActorCalculator::BeginPlay()
{
	Super::BeginPlay();
	Calculations* calculations = new Calculations();
	
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Sum: %f"), calculations->Summed(SetA, SetB)));
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Subtraction: %f"), calculations->Subtracted(SetA, SetB)));
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Mulplication: %f"), calculations->Multiplicated(SetA, SetB)));
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Division: %f"), calculations->Divided(SetA, SetB)));
}

// Called every frame
void ACP_ActorCalculator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

