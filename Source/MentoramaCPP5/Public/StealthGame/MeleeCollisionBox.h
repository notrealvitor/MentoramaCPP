// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MeleeCollisionBox.generated.h"

UCLASS()
class MENTORAMACPP5_API AMeleeCollisionBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeCollisionBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomCollisionParameters", meta=(ExposeOnSpawn=true))
	FName CollisionPreset = "MeleeBox";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CustomCollisionParameters", meta=(ExposeOnSpawn=true))
	FVector CollisionExtent = FVector(40.0f, 8.0f, 8.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CustomCollisionParameters", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CustomCollisionBox;

};
