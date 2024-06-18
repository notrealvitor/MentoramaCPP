// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_BaseBTController.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	FreeRoaming UMETA(DisplayName = "FreeRoaming"),
	SeeingEnemy UMETA(DisplayName = "SeeingEnemy"),
	Fight UMETA(DisplayName = "Fighting"),
	Investigating UMETA(DisplayName = "Investigating"),
	Patrolling UMETA(DisplayName = "Patrolling"),
	Fleeing UMETA(DisplayName = "Fleeing"),
	Healing UMETA(DisplayName = "Healing"),
	ReactingDamage UMETA(DisplayName = "ReactingDamage"),
	Lifeless UMETA(DisplayName = "Lifeless")
};

UCLASS()
class MENTORAMACPP5_API AAIC_BaseBTController : public AAIController
{
	GENERATED_BODY()
	
};
