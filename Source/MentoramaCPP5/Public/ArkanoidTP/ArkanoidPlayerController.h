// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnableLaunch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisableLaunch);

class UInputMappingContext;
DECLARE_LOG_CATEGORY_EXTERN(LogArkanoidCharacter, Log, All);

UCLASS()
class MENTORAMACPP5_API AArkanoidPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABall* SpawnBall();

	void Tick(float DeltaSeconds) override;
	
	void EnableLaunch();

	void DisableLaunch();
	
	
	void LaunchHoldingBall();

	UPROPERTY(EditAnywhere, Category = Ball)
	FVector OffsetSpawnInitialBall = FVector(0,0,40);

	UPROPERTY(EditAnywhere, Category = Ball)
	TSubclassOf<ABall> BallClass;

	UPROPERTY(BlueprintReadWrite)
	ABall* HoldingBall;

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FEnableLaunch OnEnableLaunch;
	UPROPERTY(BlueprintAssignable, Category = "Test")
	FDisableLaunch OnDisableLaunch;

protected:
	virtual void BeginPlay() override;
	
private:

};
