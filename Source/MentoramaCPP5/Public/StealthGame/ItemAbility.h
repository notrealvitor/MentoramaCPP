// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityAnimNotifyState.h"
#include "Animation/AnimMontage.h"
#include "UObject/NoExportTypes.h"
#include "ItemAbility.generated.h"

class APlayerController;
class AMentoramaCPP5Character;
class UAnimMontage;
class UAnimNotifyState;
class UAbilityAnimNotify;

UCLASS(Blueprintable)
class MENTORAMACPP5_API UItemAbility : public UObject
{
	GENERATED_BODY()

public:
	UItemAbility();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAbility)
	TArray<UAnimMontage*> AbilityMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemAbility)
	float AnimSpeed = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = ItemAbility)
	int ComboIndex;


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
	void ResetComboIndexIfInactive();
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
protected:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
