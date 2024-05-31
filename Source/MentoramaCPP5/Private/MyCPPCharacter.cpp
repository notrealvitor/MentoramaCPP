// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCPPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyCppBaseMode.h"



// Sets default values
AMyCPPCharacter::AMyCPPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCPPCharacter::BeginPlay()
{
	Health = MaxHealth;
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCPPCharacter::StaticClass(), FoundActors);
}

void AMyCPPCharacter::SetupPlayerInputComponent (UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
}

void AMyCPPCharacter::Attack(int Damage)
{
	HandleDamage(Damage);
}

void AMyCPPCharacter::HandleDamage(int Damage)
{
	Health -= Damage;
	OnMyHealthChanged.Broadcast(Health);
	if(Health <= 0)
	{
		ShowDeathFeedback();
		auto* gameMode = GetWorld()->GetAuthGameMode<AMyCppBaseMode>();
		if(!IsValid(gameMode))
		{
			gameMode->SetPlayerIsDead();
		}
		SetLifeSpan(1);
	}
}

void AMyCPPCharacter::HandleCollectibles(int Collected)
{
	Collectibles += Collected;
	OnMyCollectiblesChanged.Broadcast(Collectibles);
}





