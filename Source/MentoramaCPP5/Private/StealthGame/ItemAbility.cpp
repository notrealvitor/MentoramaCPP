// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/ItemAbility.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "MentoramaCPP5Character.h"
#include "StealthGame/AbilityAnimNotify.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Logging/StructuredLog.h"


UItemAbility::UItemAbility()
	: bTickEnabled(false)
{
	UWorld* World = GetWorld();
	if (World)
	{
		PlayerControllerReference = World->GetFirstPlayerController();
		PlayerCharacter = Cast<AMentoramaCPP5Character>(PlayerControllerReference->GetPawn());
	}	
}

void UItemAbility::Tick_Implementation(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("UTickableUObject is ticking"));
}

TStatId UItemAbility::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UTickableUObject, STATGROUP_Tickables);
}

bool UItemAbility::IsTickable() const
{
	return bTickEnabled;
}

void UItemAbility::SetTickEnabled(bool bEnabled)
{
	bTickEnabled = bEnabled;
}


void UItemAbility::TriggerAbility_Implementation()
{
	if (!PlayerControllerReference) return;			
	if (!PlayerCharacter)  return;
		if (!PlayerCharacter->AbilityPlaying)
		{
			PlayerCharacter->Cooldown = ItemSlot->Cooldown;
			UE_LOGFMT(LogTemp, Error, "How much is the itemslot CooldDown: -> {0}", ItemSlot->Cooldown);
			UE_LOG(LogTemp, Warning, TEXT("CANCOMBO %s, AbilityPLaying %s, IsInCombo %s"),CanCombo ? TEXT("true") : TEXT("false"), PlayerCharacter->AbilityPlaying ? TEXT("true") : TEXT("false"), IsInCombo ? TEXT("true") : TEXT("false"));
			if (CanCombo)
			{
				EnableMeleeCollisions(); //THIS COLLISION IS BETTER TO BE ACTIVATED IN THE NOTIFY OF THE ANIMATIONS, THIS IS JUST FOR PROTOTYPING 
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
				
				EnableMeleeCollisions(); //THIS COLLISION IS BETTER TO BE ACTIVATED IN THE NOTIFY OF THE ANIMATIONS, THIS IS JUST FOR PROTOTYPING 
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

void UItemAbility::EnableMeleeCollisions()
{
	//THIS COLLISION IS BETTER TO BE ACTIVATED IN THE NOTIFY OF THE ANIMATIONS, THIS IS JUST FOR PROTOTYPING 
	for (auto& CollisionComponent : PlayerCharacter->SpawnedMeleeCollisions)
	{
		if (CollisionComponent && CollisionComponent->CustomCollisionBox)
		{
			CollisionComponent->CustomCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}

void UItemAbility::DisableMeleeCollisions()
{
		//THIS COLLISION IS BETTER TO BE ACTIVATED IN THE NOTIFY OF THE ANIMATIONS, THIS IS JUST FOR PROTOTYPING 
		for (auto& CollisionComponent : PlayerCharacter->SpawnedMeleeCollisions)
		{
			if (CollisionComponent && CollisionComponent->CustomCollisionBox)
			{
				CollisionComponent->CustomCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
}

void UItemAbility::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) 
	{
		
		if (!bIsInternalInterrupt)
		{	
			UE_LOG(LogTemp, Warning, TEXT("Animation Montage Interrupted by an external actor."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Animation Montage Interrupted intentionally by the character."));
		}
		bIsInternalInterrupt = false; //should set back to false until next advise
		DisableMeleeCollisions();
		
	}
	else
	{
		PlayerCharacter->SetAbilityPlaying(false);
		DisableMeleeCollisions();
		IsInCombo = false;
		if (ComboIndex >= AbilityMontage.Num() - 1 ) // we dont add the -1 here because the ComboIndex is incremented after the execution
		{
			ResetFlowVariables();
		}
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