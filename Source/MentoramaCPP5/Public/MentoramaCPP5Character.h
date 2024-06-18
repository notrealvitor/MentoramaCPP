// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "StealthGame/Interactions.h"
#include "StealthGame/ItemSlot.h"
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


public:
	AMentoramaCPP5Character(); //this character is parent for the Player Character and also the AI Characters, only stuff regarding both should be added

protected:

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact();

	UPROPERTY(BlueprintReadWrite)
	bool AbilityPlaying = false;

	void SetAbilityPlaying(bool SetState);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") //this stopped being valid for some reason, had to implement from blueprint
	// UCharacterStatsComponent* CharacterStatsComp;
};

