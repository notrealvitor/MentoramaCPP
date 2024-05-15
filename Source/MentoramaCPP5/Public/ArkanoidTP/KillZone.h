// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class MENTORAMACPP5_API AKillZone : public AActor
{
	GENERATED_BODY()

	AKillZone();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
