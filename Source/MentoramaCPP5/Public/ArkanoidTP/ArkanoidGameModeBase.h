// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "ArkanoidGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStart, int, Round);

UCLASS()
class MENTORAMACPP5_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AArkanoidGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class ABrickManager* BrickManager;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation = FVector(0,0,0);

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<ABrickManager> BrickManagerClass;

	int DeathRestartTimer;

	UPROPERTY(BlueprintAssignable)
	FOnRoundStart OnRoundStart;

	UPROPERTY(BlueprintReadWrite)
	int CurrentRound = 0;

	UFUNCTION(BlueprintCallable)
	void StartRound(int Round, int NRows, int NColumns, int BrickHealth);

	
protected:

	UFUNCTION()
	void EndRound();

	void SpawnBrickManager();
};
