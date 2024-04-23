// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyCppBaseMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMyGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMyGameWon);

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API AMyCppBaseMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerIsDead();
	//Create an objective for the game mode
	UFUNCTION(BlueprintCallable)
	void RegisterObjective();
	//When an objetive is completed this is called.
	UFUNCTION(BlueprintCallable)
	void UnregisterObjective();

	UPROPERTY(BlueprintAssignable)
	FOnMyGameOver OnMyGameOver;
	UPROPERTY(BlueprintAssignable)
	FOnMyGameWon OnMyGameWon;
	
protected:
	bool HasGameEnded = false;
	int ObjectivesCount = 0;
	
};
