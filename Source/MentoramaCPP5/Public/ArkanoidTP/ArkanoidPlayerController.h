// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
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


	ABall* SpawnBall();

	UFUNCTION(BlueprintImplementableEvent)
	void EventBallDestroyed();
	
	UFUNCTION(BlueprintCallable)
	void DestroyBall(ABall* Ball);

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void EnableLaunch();

	void DisableLaunch();
	
	
	void LaunchHoldingBall();

	UPROPERTY(EditAnywhere, Category = Ball)
	FVector OffsetSpawnInitialBall = FVector(0,0,40);

	UPROPERTY(EditAnywhere, Category = Ball)
	TSubclassOf<ABall> BallClass;

	UPROPERTY(BlueprintReadWrite)
	ABall* HoldingBall;

	UPROPERTY(BlueprintAssignable)
	FEnableLaunch OnEnableLaunch;
	UPROPERTY(BlueprintAssignable)
	FDisableLaunch OnDisableLaunch;
	UPROPERTY(BlueprintAssignable)
	FEndGame OnEndGame;
	
	int BricksCreated;
	int BricksDestroyed;

	UFUNCTION(BlueprintCallable)
	void DestroyAllBalls();

	UPROPERTY(BlueprintReadOnly)
	TArray<ABall*> Balls;
	
protected:

	

	UFUNCTION()
	void OnBallDestroyed(ABall* ball);

	
private:

};
