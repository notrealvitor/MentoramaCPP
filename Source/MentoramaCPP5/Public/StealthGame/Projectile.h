// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MENTORAMACPP5_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn=true))
	float BaseDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const float DeltaT);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
