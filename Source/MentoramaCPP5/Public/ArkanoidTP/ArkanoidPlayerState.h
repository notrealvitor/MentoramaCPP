// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API AArkanoidPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int StartingLives = 3;
	
	UPROPERTY(BlueprintReadWrite)
	int Lives;

	
};
