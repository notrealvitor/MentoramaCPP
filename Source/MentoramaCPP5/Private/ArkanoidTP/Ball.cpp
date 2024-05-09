// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/Ball.h"

#include "MentoramaCPP5Character.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::Launch()
{
	LaunchDirection = FVector(0,cos(FMath::DegreesToRadians(LaunchAngle)), sin(FMath::DegreesToRadians(LaunchAngle))); //update
	Sphere->AddImpulse(LaunchDirection * LaunchSpeed, NAME_None, true);
	//UE_LOG(LogTemplateCharacter, Error, TEXT("LaunchDirection '%s' and Launch Angle %f"), *LaunchDirection.ToString(), LaunchAngle);				//log print with two examples with float and vector3
}

