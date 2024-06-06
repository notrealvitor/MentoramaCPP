// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviourComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UAIBehaviourComponent::UAIBehaviourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UAIBehaviourComponent::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::PrintString(this, TEXT("Started AI character"), 1);
	// Initialize OwnerAICharacter
	OwnerAICharacter = Cast<AAI_Character>(GetOwner());

	 if (OwnerAICharacter)
	 {
	 	OwnerAICharacter->FindComponentByClass<UCharacterMovementComponent>()->MaxWalkSpeed = CharacterSpeed;
	 	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Initialized OwnerAICharacter successfully: %s"), *OwnerAICharacter->GetName()), 1);
	 }
	 else
	 {
	 	UKismetSystemLibrary::PrintString(this, TEXT("Failed to initialize OwnerAICharacter"), 1);
	 }
	
}

// Called every frame
void UAIBehaviourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(bCanMove&&bIsAlive)
	{
		EnemyBehaviour(DeltaTime);
	}
	// ...
}

void UAIBehaviourComponent::EnemyBehaviour(float DeltaTime)   //Exerc�cio do M7
{
	 if (!OwnerAICharacter)   //Cancel the Move if the OwnerCharacterIsNotValid
	 {
	 	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("CHARACTER FROM AIBEHAVIOUR IS INVALID") ), 1);
	 	return;
	 }
	 switch (OwnerAICharacter->E_AIHealthState)  //Control enemy actions depending on its current Health.
	 {
	 case EHealthState::FullHealth: 
	 	switch (E_AIState)
	 	{
	 		case EState::Idle:
	 			OwnerAICharacter->Idle();
	 			break;
	 		case EState::Attacking:
	 			OwnerAICharacter->Attacking();
	 			break;
	 		case EState::Roaming:
	 			OwnerAICharacter->Roaming();
	 			break;
	 		case EState::PatrolWaypoints:
	 			OwnerAICharacter->PatrolWaypoints(TimeBeforeTurn);
	 			break;
	 		case EState::LookAtWaypoints:
	 			OwnerAICharacter->LookAtWaypoints(TimeBeforeTurn);
	 			break;
	 	}
	 	break;
	 case EHealthState::Recovery:
	 	OwnerAICharacter->PrintAction("Recovery: May recover if possible", 0);
	 	OwnerAICharacter->IncreaseHealth(DeltaTime * 2);														 //must be called in target Character
	 	if (OwnerAICharacter->S_AIData.Health <= 30 || OwnerAICharacter->S_AIData.Health >= 60)				//must be called in target Character
	 	{
	 		OwnerAICharacter->SetHealthState();
	 	}
	 	break;
	 case EHealthState::Endangered:
	 	OwnerAICharacter->PrintAction("Danger: Run and Recover Immediately", 0);
	 	OwnerAICharacter->IncreaseHealth(DeltaTime * 5);
	 	if (OwnerAICharacter->S_AIData.Health <= 0 || OwnerAICharacter->S_AIData.Health > 30)					  //must be called in target Character
	 	{
	 		OwnerAICharacter->SetHealthState();
	 	}
	 	break;
	 case EHealthState::Dead:
	 	OwnerAICharacter->PrintAction("Dead", 0);
	 	break;
	 }
}
