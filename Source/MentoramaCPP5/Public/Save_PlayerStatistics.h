// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save_PlayerStatistics.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API USave_PlayerStatistics : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int FailCount;
	
};
