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
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentInteractionsChanged, TScriptInterface<IInteractions>, NewInteractible);

UCLASS(config=Game)
class AMentoramaCPP5Character : public ACharacter ,public IInteractions
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
public:
	AMentoramaCPP5Character();
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractionSuccessful();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void Interact();

	UPROPERTY(BlueprintReadWrite)
	UItemSlot* SelectedItemSlot;	

	UFUNCTION(BlueprintImplementableEvent)
	USceneComponent* GetCamera() const;

	virtual void InteractionAction_Implementation(AActor* Interactor, UItemSlot* InteractorItem) override; // dont forget to add the public IInteractions into the class call
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsAlive = true;

	bool bTraceIsHit;
	
	FHitResult TraceResult;

	void AimTrace(bool Debug);

	UPROPERTY(BlueprintAssignable)
	FOnCurrentInteractionsChanged OnCurrentInteractionsChanged;

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IInteractions> CurrentInteractable;

	UPROPERTY(BlueprintReadWrite)
	float TraceRange = 200;

	UPROPERTY(BlueprintReadWrite)
	bool AbilityPlaying = false;

	void SetAbilityPlaying(bool SetState);
};

