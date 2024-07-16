// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 300.f;
	BaseDamage = 50;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
		
}

void AProjectile::MoveForward(const float DeltaT)
{
	AddActorWorldOffset(GetActorForwardVector() * DeltaT * Speed);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(DeltaTime);

}

