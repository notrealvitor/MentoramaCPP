// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cpp_Collectible.generated.h"

UCLASS()
class MENTORAMACPP5_API Acpp_Collectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acpp_Collectible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Quantity = 10;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USphereComponent* pickUpSphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystem* UPickUpParticles;

	UFUNCTION()
	void OnEnterPickUpSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent) //this allows the event to be overriden in the blueprint (I dont know why exactly)
	void OnPickUpStart();

	UFUNCTION(BlueprintCallable)
	void OnPickUpFinished();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* InteractActor;

};
