// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/PlayerPaddler.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "Misc/App.h"
#include "MentoramaCPP5Character.h"
#include "GameFramework/GameSession.h"

// Sets default values
APlayerPaddler::APlayerPaddler()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPaddler::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerPaddler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPaddler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(HorizontalMoveAction, ETriggerEvent::Triggered, this, &APlayerPaddler::HorizontalMove);
		EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Triggered, this, &APlayerPaddler::LaunchBall);
	}
}



void APlayerPaddler::HorizontalMove(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector movementInput = ConsumeMovementInputVector();
		//AddActorLocalOffset(movementInput * MoveSpeed , true);
		AddActorWorldOffset(FVector(0, Value.Get<float>() * MoveSpeed * FApp::GetDeltaTime(), 0), true);
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' FailedMovementInput A or S"), *movementInput.ToString());		//log print  example with string
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%f' FailedMovementInput A or S"), Value.Get<float>());				//log print example with float
	}
}

void APlayerPaddler::LaunchBall()
{
	if (Controller != nullptr)
	{
		Cast<AArkanoidPlayerController>(GetController())->LaunchHoldingBall();
	}
}

