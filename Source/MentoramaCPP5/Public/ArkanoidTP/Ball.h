// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallDestroyed, ABall*, Ball);

UCLASS()
class MENTORAMACPP5_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Sphere;

	void Launch();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LaunchDirection = FVector(0,cos(FMath::DegreesToRadians(LaunchAngle)), sin(FMath::DegreesToRadians(LaunchAngle)));

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LaunchSpeed = 1500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LaunchAngle = 90;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentSpeed;
	
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyFeedback();

	UFUNCTION(BlueprintCallable)
	void DestroyBall();

	UPROPERTY(BlueprintAssignable)
	FOnBallDestroyed OnBallDestroyed;

	void Kill();
};
