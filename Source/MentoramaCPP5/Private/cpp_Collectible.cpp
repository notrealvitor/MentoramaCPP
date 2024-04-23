// Fill out your copyright notice in the Description page of Project Settings.


#include "cpp_Collectible.h"
#include "Components/SphereComponent.h"
#include "MyCPPCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
Acpp_Collectible::Acpp_Collectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pickUpSphere = CreateDefaultSubobject<USphereComponent>("pickUpSphere");
	pickUpSphere->SetupAttachment(RootComponent);
	pickUpSphere->OnComponentBeginOverlap.AddDynamic(this, &Acpp_Collectible::OnEnterPickUpSphere);

}

// Called when the game starts or when spawned
void Acpp_Collectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acpp_Collectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Acpp_Collectible::OnPickUpStart_Implementation()  //the _Implementation is necessary for the function compile
{

}

void Acpp_Collectible::OnEnterPickUpSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractActor = OtherActor;
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UPickUPParticles*);
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UPickUPParticles, GetActorLocation(), FRotator::ZeroRotator, true);
	OnPickUpStart();
}

void Acpp_Collectible::OnPickUpFinished()
{
	AMyCPPCharacter* playerCharacter = Cast<AMyCPPCharacter>(InteractActor);
	if(IsValid(playerCharacter))
	{
		playerCharacter->HandleCollectibles(Quantity);
	}
	else
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s cast failed to %s"), *UKismetSystemLibrary::GetDisplayName(InteractActor), *UKismetSystemLibrary::GetDisplayName(playerCharacter)), true, true, FColor::Red, 5);
}
