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


