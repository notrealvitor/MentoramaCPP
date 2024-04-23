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

public:
	// Sets default values for this character's properties
	AMyCPPCharacter();

	void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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

