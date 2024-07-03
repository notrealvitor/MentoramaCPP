// Copyright Epic Games, Inc. All Rights Reserved.

#include "MentoramaCPP5Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "StealthGame/CharacterStatsComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMentoramaCPP5Character::AMentoramaCPP5Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//CharacterStatsComp = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("CharacterStatsComp"));
	//AddInstanceComponent(AIBehaviourComp);
	//AddOwnedComponent(CharacterStatsComp);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

}

void AMentoramaCPP5Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

void AMentoramaCPP5Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AMentoramaCPP5Character::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("MentoramaMyCPPCharacter is interacting"));
}

void AMentoramaCPP5Character::SetAbilityPlaying(bool SetState)
{
	AbilityPlaying = SetState;
}

void AMentoramaCPP5Character::ApplyRotationOverTime(FRotator InTargetRotation, float Duration)
{
	DesiredRotation = InTargetRotation;
	TotalDuration = Duration;
	TimeElapsed = 0.0f;
	InitialRotation = GetActorRotation();

	// Start the timer to call RotateActor at a regular interval
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Rotation, this, &AMentoramaCPP5Character::RotateActor, GetWorld()->GetDeltaSeconds(), true);
}

void AMentoramaCPP5Character::RotateActor()
{
	TimeElapsed += GetWorld()->GetDeltaSeconds();

	// Calculate the current interpolation alpha value
	float Alpha = FMath::Clamp(TimeElapsed / TotalDuration, 0.0f, 1.0f);

	// Interpolate the rotation towards the desired rotation
	FRotator NewRotation = FMath::Lerp(InitialRotation, DesiredRotation, Alpha);

	// Set the new rotation
	SetActorRotation(NewRotation);

	// Check if the rotation is complete
	if (Alpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Rotation);
	}
}

void AMentoramaCPP5Character::GetStunned(float Duration)
{
	bIsStunned = true;
	GetWorld()->GetTimerManager().SetTimer(StunnedTimerHandle, this, &AMentoramaCPP5Character::ResetStunned, Duration, false);
}

void AMentoramaCPP5Character::ResetStunned()
{
	bIsStunned = false;
}
