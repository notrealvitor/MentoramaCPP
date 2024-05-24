// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/Ball.h"
#include "MentoramaCPP5Character.h"
#include "ArkanoidTP/ArkanoidPlayerController.h"
#include "Math/UnitConversion.h"

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
	// this is one solution for maintaining velocity and prevent the full horizontal/vertical ball bug (did not fix for me, mine is currently in the BP)
	// if(CurrentSpeed <= 0 ) return;
	// FVector velocity = GetVelocity();
	//
	// if (velocity.IsNearlyZero()) return;
	//
	// velocity.Normalize();
	// const float Tolerance = 0.1f;
	// if (FMath::IsNearlyZero(velocity.X, Tolerance))
	// {
	// 	velocity.X = Tolerance * FMath::RandBool() ? 1 : -1;
	// }
	// if (FMath::IsNearlyZero(velocity.Z, Tolerance))
	// {
	// 	velocity.Z = Tolerance * FMath::RandBool() ? 1 : -1;
	// }
	// velocity.Normalize();
	// velocity *= CurrentSpeed;
	// Sphere->SetPhysicsLinearVelocity(velocity);
}

void ABall::Launch()
{
	LaunchDirection = FVector(0,cos(FMath::DegreesToRadians(LaunchAngle)), sin(FMath::DegreesToRadians(LaunchAngle)));				//update
	//UE_LOG(LogTemplateCharacter, Error, TEXT("LaunchDirection '%s' and Launch Angle %f"), *LaunchDirection.ToString(), LaunchAngle);				//log print with two examples with float and vector3
	Sphere->AddImpulse(LaunchDirection * LaunchSpeed, NAME_None, true);
	CurrentSpeed = LaunchSpeed;
}

void ABall::DestroyBall()
{
	DestroyFeedback();
	Destroy();
}

void ABall::Kill()
{
	OnBallDestroyed.Broadcast(this);
	Destroy();
}


