// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "StealthGame/Interactions.h"
#include "StealthGame/MeleeCollisionBox.h"
#include "MentoramaCPP5Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCharacterStatsComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentInteractionsChanged, TScriptInterface<IInteractions>, NewInteractible);

UCLASS(config=Game)
class AMentoramaCPP5Character : public ACharacter ,public IInteractions
{
	GENERATED_BODY()

protected:

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;


public:
	AMentoramaCPP5Character(); //this character is parent for the Player Character and also the AI Characters, only stuff regarding both should be added

	UFUNCTION(BlueprintCallable, Category = "NotCharacter")
	virtual void Interact();

	UPROPERTY(BlueprintReadWrite, Category = "NotCharacter")
	bool AbilityPlaying = false;

	UPROPERTY(BlueprintReadWrite, Category = "NotCharacter")
	float Cooldown = 0;

	UPROPERTY(BlueprintReadWrite, Category = "NotCharacter")
	bool bIsStunned;

	void SetAbilityPlaying(bool SetState);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") //this stopped being valid for some reason, had to implement from blueprint
	// UCharacterStatsComponent* CharacterStatsComp;

	UFUNCTION(BlueprintCallable, Category = "NotCharacter")
	void ApplyRotationOverTime(FRotator TargetRotation, float Duration);

	//Being stunned means the character should not be able to do actions like attack, move or jump
	UFUNCTION(BlueprintCallable, Category = "NotCharacter")
	void GetStunned(float Duration = 0.1f);

	UPROPERTY(BlueprintReadWrite)
	TArray<AMeleeCollisionBox*> SpawnedMeleeCollisions;

private:
	// Helper function
	void RotateActor();
	void ResetStunned();
	FTimerHandle StunnedTimerHandle;

	// Member variables to store rotation details
	FRotator InitialRotation;
	FRotator DesiredRotation;
	float TotalDuration;
	float TimeElapsed;
	FTimerHandle TimerHandle_Rotation;

};

