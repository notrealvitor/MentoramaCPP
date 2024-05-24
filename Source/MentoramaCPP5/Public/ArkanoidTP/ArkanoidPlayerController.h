// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "NotPlayerProperties.h"
#include "MentoramaGameInstance.h"
#include "ArkanoidPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnableLaunch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisableLaunch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndGame);

class UInputMappingContext;
DECLARE_LOG_CATEGORY_EXTERN(LogArkanoidCharacter, Log, All);

UCLASS()
class MENTORAMACPP5_API AArkanoidPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	// Balls
	UPROPERTY(EditAnywhere, Category = Ball)
	TSubclassOf<ABall> BallClass;
	UPROPERTY(EditAnywhere, Category = Ball)
	FVector OffsetSpawnInitialBall = FVector(0,0,80);
	ABall* SpawnBall();
	UPROPERTY(BlueprintReadWrite)
	ABall* HoldingBall;
	void LaunchHoldingBall();
	UFUNCTION(BlueprintCallable)
	void DestroyBall(ABall* Ball);
	UPROPERTY(BlueprintReadOnly)
	TArray<ABall*> Balls;
	UFUNCTION(BlueprintCallable)
	void DestroyAllBalls();
	UFUNCTION(BlueprintImplementableEvent)
	void EventBallDestroyed();
	UPROPERTY(BlueprintReadWrite)
	int SpawnBallDamage = 1;
	
	//Launching the ball
	int CurrentLives = 77; //if it shows 77 values are not being set
	UFUNCTION(BlueprintCallable)
	void EnableLaunch();
	void DisableLaunch();
	UPROPERTY(BlueprintAssignable)
	FEnableLaunch OnEnableLaunch;
	UPROPERTY(BlueprintAssignable)
	FDisableLaunch OnDisableLaunch;
	UPROPERTY(BlueprintAssignable)
	FEndGame OnEndGame;
	UPROPERTY(BlueprintReadWrite)
	bool GameRunning = true;
	
	//Bricks
	int BricksCreated;
	int BricksDestroyed;

	//System References
	UPROPERTY(BlueprintReadOnly)
	UNotPlayerProperties* VM_NotPlayerProperties;
	UPROPERTY()
	UMentoramaGameInstance* MyMentoramaGameInstance;

};
