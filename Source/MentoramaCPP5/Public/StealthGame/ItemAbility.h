// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAnimNotifyState.h"
#include "Animation/AnimMontage.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "ItemAbility.generated.h"

class APlayerController;
class AMentoramaCPP5Character;
class UAnimMontage;
class UAnimNotifyState;
class UAbilityAnimNotify;

UCLASS(Blueprintable)
class MENTORAMACPP5_API UItemAbility : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UItemAbility();

	// Begin FTickableGameObject interface
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void Tick(float DeltaTime);
	
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	// End FTickableGameObject interface

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetTickEnabled(bool bEnabled);
	
	// End UObject interface
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAbility)
	TArray<UAnimMontage*> AbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAbility)
	float AnimSpeed = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = ItemAbility)
	int ComboIndex;

	UPROPERTY(BlueprintReadWrite, Category = ItemAbility)
	class UItemSlot* ItemSlot;


	//this setup allows us to set the trigger ability implementation and then overwrite it in blueprints if necessary
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = ItemAbility)
	void TriggerAbility();
	virtual void TriggerAbility_Implementation();

	// Expose the player controller reference to Blueprints
	UPROPERTY(BlueprintReadOnly, Category="Player")
	APlayerController* PlayerControllerReference;

	AMentoramaCPP5Character* PlayerCharacter;

	UAbilityAnimNotify* AbilityNotify;
	UAbilityAnimNotifyState* AbilityNotifyState;

	void SetMontageNotifiesOwners();
	void PlayAbilityMontage();
	
	void AdviseInternalInterruptMontage();
	bool bIsInternalInterrupt = true;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ItemAbility)
	bool CanCombo;
	UPROPERTY(BlueprintReadWrite, Category = ItemAbility)
	bool IsInCombo;

	float LastCallTime; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ItemAbility)
	bool ComboOnStateEnding = true; //still testing, lets keep true for no

	void ResetFlowVariables();

private:
	bool bTickEnabled;
	
protected:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
