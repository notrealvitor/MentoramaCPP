// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/KillZone.h"

#include "ArkanoidTP/Ball.h"

AKillZone::AKillZone()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	auto* Ball = Cast<ABall>(OtherActor);
	if (IsValid(Ball))
	{
		Ball->Kill();
	}
}
