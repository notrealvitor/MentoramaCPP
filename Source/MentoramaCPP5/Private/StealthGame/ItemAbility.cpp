// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/ItemAbility.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "MentoramaCPP5Character.h"
#include "StealthGame/AbilityAnimNotify.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"


UItemAbility::UItemAbility()
{
	UWorld* World = GetWorld();
	if (World)
	{
		PlayerControllerReference = World->GetFirstPlayerController();
		PlayerCharacter = Cast<AMentoramaCPP5Character>(PlayerControllerReference->GetPawn());
	}	
}

void UItemAbility::TriggerAbility_Implementation()
{
	if (!PlayerControllerReference) return;			
	if (!PlayerCharacter)  return;
		if (!PlayerCharacter->AbilityPlaying)
		{
			UE_LOG(LogTemp, Warning, TEXT("CANCOMBO %s, AbilityPLaying %s, IsInCombo %s"),CanCombo ? TEXT("true") : TEXT("false"), PlayerCharacter->AbilityPlaying ? TEXT("true") : TEXT("false"), IsInCombo ? TEXT("true") : TEXT("false"));
			if (CanCombo)
			{
				PlayerCharacter->SetAbilityPlaying(true);
				IsInCombo = true;
				CanCombo = false;
				ComboIndex++;
				ComboIndex = FMath::Clamp(ComboIndex, 0, AbilityMontage.Num() - 1);
				AdviseInternalInterruptMontage();
				PlayAbilityMontage();
			}
			else if (!IsInCombo)			
			{
				PlayerCharacter->SetAbilityPlaying(true);
				ResetFlowVariables();
				PlayAbilityMontage();
				
			}
			
		}
}

void UItemAbility::PlayAbilityMontage()
{
	UAnimInstance* AnimInstance = PlayerCharacter->GetMesh()->GetAnimInstance();
	if (AnimInstance && AbilityMontage.IsValidIndex(ComboIndex) && AbilityMontage[ComboIndex]) // Ensure AbilityMontage is set
	{
		//UE_LOG(LogTemp, Warning, TEXT("Animation Montage Triggered %hhd"),AbilityPlaying);
		//Sets the montage to play and so we can know when it is ended
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &UItemAbility::OnMontageEnded);				
		AnimInstance->Montage_Play(AbilityMontage[ComboIndex], AnimSpeed);
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AbilityMontage[ComboIndex]);

		//Pass this ItemAbility to the notifies so they can manage its variables inside the animation directly
		SetMontageNotifiesOwners();

		UE_LOG(LogTemp, Warning, TEXT("PLAYABILITYMONTAGE: COMBO INDEX %i"),ComboIndex);
	}				
}

void UItemAbility::AdviseInternalInterruptMontage() //animation interrupts are seeing as intentionals unless it is advised first
{
	bIsInternalInterrupt = true;
}

void UItemAbility::ResetFlowVariables()
{
	IsInCombo = false;
	CanCombo = false;
	ComboIndex = 0;
}

void UItemAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) 
	{
		
		if (!bIsInternalInterrupt)
		{	//MAYBE WE SHOULD LET THE ON DAMAGE DEAL WITH THIS
			// PlayerCharacter->SetAbilityPlaying(false);
			// if (ComboIndex >= AbilityMontage.Num())//-1) // we dont add the -1 here because the ComboIndex is incremented after the execution
			// {
			// 	ComboIndex = 0;
			// }
			// ResetFlowVariables();
			// ResetComboIndexIfInactive();
			UE_LOG(LogTemp, Warning, TEXT("Animation Montage Interrupted by an external actor."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Animation Montage Interrupted intentionally by the character."));
		}
		bIsInternalInterrupt = false; //should set back to false until next advise
		
	}
	else
	{
		PlayerCharacter->SetAbilityPlaying(false);
		IsInCombo = false;
		if (ComboIndex >= AbilityMontage.Num() - 1 ) // we dont add the -1 here because the ComboIndex is incremented after the execution
		{
			ResetFlowVariables();
		}
		else ResetComboIndexIfInactive();				
		UE_LOG(LogTemp, Log, TEXT("Animation Montage Ended."));		
	}
}

void UItemAbility::SetMontageNotifiesOwners() 	//here we want to look if our custom notify CPP is present in the montage and if it is, we tell it who is the ability that called it
{
	if (AbilityMontage[ComboIndex])
	{
		// Iterate through the notifies and notifystates in the montage
		for (const FAnimNotifyEvent& NotifyEvent : AbilityMontage[ComboIndex]->Notifies)
		{
			if (NotifyEvent.Notify)
			{
				UAbilityAnimNotify* ExistingNotify = Cast<UAbilityAnimNotify>(NotifyEvent.Notify); //here we make sure the notify is one of our AbilityAnimNotify
				if (ExistingNotify)
				{
					AbilityNotify = ExistingNotify;
					if (AbilityNotify)
					{
						AbilityNotify->ItemAbilityOwner = this;
					}
					//UE_LOG(LogTemp, Log, TEXT("MontageTest, found notify?: %s"), *AbilityNotify->GetName());
				}
			}
			if (NotifyEvent.NotifyStateClass)
			{
				UAbilityAnimNotifyState* ExistingNotify = Cast<UAbilityAnimNotifyState>(NotifyEvent.NotifyStateClass); //here we make sure the notify is one of our AbilityAnimNotifyState
				if (ExistingNotify)
				{
					AbilityNotifyState = ExistingNotify;
					if (AbilityNotifyState)
					{
						AbilityNotifyState->ItemAbilityOwner = this;
					}
					//UE_LOG(LogTemp, Log, TEXT("MontageTest, found notify?: %s"), *AbilityNotifyState->GetName());
				}
			}
		}
	}
}

void UItemAbility::ResetComboIndexIfInactive()
{
	//CHECK IF SHOULD RESET INDEX
	// float CurrentGameTime = 0.0f;
	// if (GetWorld())
	// {
	// 	CurrentGameTime = GetWorld()->GetTimeSeconds();
	// } else return;
	// if (CurrentGameTime - LastCallTime > 3)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("More than 1 second has passed since the last call, setting the ComboIndex back to zero."));
	// 	ComboIndex = 0;
	// 	LastCallTime = GetWorld()->GetTimeSeconds();
	// }
}




