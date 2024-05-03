// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MentoramaCPP5Character.h"
#include "ArkanoidTPChar.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API AArkanoidTPChar : public AMentoramaCPP5Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArkanoidTPChar();

	void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupArkanoidInputComponent(class UInputComponent* PlayerInputComponent);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float Health = MaxHealth;
	

protected:

	/** Called for movement input */
	void MovePaddler(const FInputActionValue& Value);

	
};
