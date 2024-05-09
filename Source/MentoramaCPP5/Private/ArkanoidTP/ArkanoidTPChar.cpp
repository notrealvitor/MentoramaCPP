// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/ArkanoidTPChar.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AArkanoidTPChar::AArkanoidTPChar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AArkanoidTPChar::BeginPlay()
{
	Health = MaxHealth;
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
}

void AArkanoidTPChar::SetupPlayerInputComponent (UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	AArkanoidTPChar::SetupArkanoidInputComponent(inputComponent);
}

void AArkanoidTPChar::SetupArkanoidInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving the paddler
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AArkanoidTPChar::MovePaddler);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find Arkanoid Input Component"), *GetNameSafe(this));
	}
}

void AArkanoidTPChar::MovePaddler(const FInputActionValue& Value)
{	// input is a Vector2D
 	FVector2D MovementVector = Value.Get<FVector2D>();
 
 	if (Controller != nullptr)
 	{
 		// find out which way is forward
 		const FRotator Rotation = Controller->GetControlRotation();
 		const FRotator YawRotation(0, Rotation.Yaw, 0);
 
 		// get right vector 
 		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
 		// add movement 
 		AddMovementInput(RightDirection, MovementVector.X);
 	}

}	