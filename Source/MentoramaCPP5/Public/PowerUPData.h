// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArkanoidTP/ArkanoidAbilityActor.h"
#include "PowerUPData.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class MENTORAMACPP5_API UPowerUPData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsonly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsonly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AArkanoidAbilityActor* AbilityActorToSpawn;
	
};
