// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CP_ActorCalculator.generated.h"

class Calculations {

public:
	Calculations(); 

	float A;
	float B;
	
	static float Summed(float A, float B) { return A + B; }
	static float Subtracted(float A, int B) { return A - B; }
	static float Divided(float A, float B) { return A / B; }
	static float Multiplicated(float A, float B) { return A * B; }

};

UCLASS()
class MENTORAMACPP5_API ACP_ActorCalculator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACP_ActorCalculator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SetA;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SetB;

};
