// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	
	UFUNCTION(BlueprintCallable)
	void MoveToPoint(FVector MovingPoint);

	UFUNCTION(BlueprintCallable)
	void LookToPoint(FVector MovingPoint);

	bool PatrolIsMoving = false;
	bool PatrolIsReturning = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector StartingPoint;


	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
};

