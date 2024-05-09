// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	
};
