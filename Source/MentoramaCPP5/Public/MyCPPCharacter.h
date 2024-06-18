// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MentoramaCPP5Character.h"
#include "GameFramework/Character.h"

#include "MyCPPCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyHealthChanged, int, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyCollectiblesChanged, int, NewCollectibles);

UCLASS()
class MENTORAMACPP5_API AMyCPPCharacter : public AMentoramaCPP5Character 
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

	
public:
	// Sets default values for this character's properties
	AMyCPPCharacter();

	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
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

	virtual void Interact() override;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractionSuccessful();

	UPROPERTY(BlueprintReadWrite)
	UItemSlot* SelectedItemSlot;	

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetCamera() const;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAlive = true;

	bool bTraceIsHit;
	
	FHitResult TraceResult;

	UPROPERTY(BlueprintAssignable)
	FOnCurrentInteractionsChanged OnCurrentInteractionsChanged;

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IInteractions> CurrentInteractable;

	UPROPERTY(BlueprintReadWrite)
	float TraceRange = 200;


	void AimTrace(bool Debug);
	
	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void Attack(int Damage = 10);

	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void HandleDamage(int Damage);

	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void HandleCollectibles(int Collected);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowDeathFeedback();
	
	UPROPERTY(BlueprintAssignable)
	FOnMyHealthChanged OnMyHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMyCollectiblesChanged OnMyCollectiblesChanged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Health = MaxHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Collectibles;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool CanControl;

	TArray<AActor> Characters;
	



};

