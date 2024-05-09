// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArkanoidPlayerController.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddler.generated.h"

UCLASS()
class MENTORAMACPP5_API APlayerPaddler : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void HorizontalMove(const FInputActionValue& Value);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	/** Move Horizontally Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* HorizontalMoveAction;

	/** Launch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* LaunchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 2000;
	
	void LaunchBall();
};
