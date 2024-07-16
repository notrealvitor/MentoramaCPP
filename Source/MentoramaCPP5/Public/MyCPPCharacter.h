// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MentoramaCPP5Character.h"
#include "MyCPPCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyHealthChanged, int, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyCollectiblesChanged, int, NewCollectibles);

UCLASS()
class MENTORAMACPP5_API AMyCPPCharacter : public AMentoramaCPP5Character 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCPPCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION(BlueprintCallable)
	USceneComponent* GetCamera() const;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void Attack(int Damage = 10);

	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void HandleCollectibles(int Collected);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Collectibles;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractionSuccessful();

	UPROPERTY(BlueprintAssignable)
	FOnMyHealthChanged OnMyHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMyCollectiblesChanged OnMyCollectiblesChanged;

	//Health and other stats are now handled in the CharacterStatsComponents, but this is still used in previous games
	//Legacy
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Health = MaxHealth;
	UFUNCTION(BlueprintCallable, Category = "MyCPPCharacter")
	void HandleDamage(int Damage);



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(BlueprintReadWrite)
	UItemSlot* SelectedItemSlot;	

	UPROPERTY(BlueprintReadWrite)
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TraceRange = 200;

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IInteractions> CurrentInteractable;

	UPROPERTY(BlueprintAssignable)
	FOnCurrentInteractionsChanged OnCurrentInteractionsChanged;

	UPROPERTY(BlueprintReadOnly)
	FHitResult TraceResult;

private:
	void AimTrace(bool Debug);
	void StunnableJump();
	void Interact();
	bool bTraceIsHit;

	TArray<AActor> Characters;
	
};

