// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/MeleeCollisionBox.h"


// Sets default values
AMeleeCollisionBox::AMeleeCollisionBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box collision component
	CustomCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CustomCollisionBox"));
	
	CustomCollisionBox->InitBoxExtent(CollisionExtent);

	CustomCollisionBox->SetCollisionProfileName(CollisionPreset);

}

// Called when the game starts or when spawned
void AMeleeCollisionBox::BeginPlay()
{
	Super::BeginPlay();

	CustomCollisionBox->InitBoxExtent(CollisionExtent);

	CustomCollisionBox->SetCollisionProfileName(CollisionPreset);

	
	
}

// Called every frame
void AMeleeCollisionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

