// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MentoramaHelpers.h"
#include "CP_ActorCalculator.h"
#include "MyAIController.h"
#include "Components/SphereComponent.h"
#include "MyCPPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCppBaseMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	damageSphere = CreateDefaultSubobject<USphereComponent>("DamageSphere");
	damageSphere->SetupAttachment(RootComponent);
	damageSphere->OnComponentBeginOverlap.AddDynamic(this, &AAI_Character::HandleDamageSphereHit);
}

Weapon::Weapon()
{
	CurrentAmmo = AmmoMagazine;
}

Weapon::~Weapon()
{
	CurrentAmmo = AmmoMagazine;
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();

	Weapon* weapon = new Weapon(); //m7

	SetHealthState();

	Calculations* calculations = new Calculations();
	StartingCharacterPoint = (Cast<AMyAIController>(GetController())->StartingPoint);
	StartingCharacterRotation = GetActorRotation();
	MarkedPoint = RotateMyVector(PatrolPoint, GetActorRotation())+GetActorLocation();
	if(bUsePatrolPoint)
	{
		Direction = PatrolPoint;
	}

	auto* gameMode = GetWorld()->GetAuthGameMode<AMyCppBaseMode>();
	if(IsValid(gameMode))
	{
		gameMode->RegisterObjective();
	}
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimePassed += DeltaTime;
	//PrintAction(FString::Printf(TEXT("health = %f"), S_AIData.Health), 0);
	//PrintAction(FString::Printf(TEXT("PatrolPoints2 = %s"), *PatrolPoint.ToString()), 0);
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAI_Character::TakingDamage(float Damage)
{
		S_AIData.Health -= Damage;
		SetHealthState();
		if (S_AIData.Health <= .0f)
		{
			auto* gameMode = GetWorld()->GetAuthGameMode<AMyCppBaseMode>();
			if(IsValid(gameMode))
			{
				gameMode->RegisterObjective();
			}
			Destroy();
		}
}

void AAI_Character::Idle()
{
	PrintAction("Idle", 0);
}

// Rotate a vector using a rotation represented by FRotator
FVector AAI_Character::RotateMyVector(const FVector& VectorToRotate, const FRotator& Rotation)
{
	// Convert the FRotator to a quaternion
	FQuat RotationQuat(Rotation);

	// Rotate the vector using the quaternion
	return RotationQuat.RotateVector(VectorToRotate);
}

void AAI_Character::PatrolWaypoints(float TimeBeforeTurn)
{
	if(TimePassed > TimeBeforeTurn)
	{
		if (Cast<AMyAIController>(GetController())->PatrolIsReturning == false)
		{
			Cast<AMyAIController>(GetController())->MoveToPoint(MarkedPoint);
		}

		if (Cast<AMyAIController>(GetController())->PatrolIsReturning == true)
		{
			Cast<AMyAIController>(GetController())->MoveToPoint(StartingCharacterPoint);
		}
	}
}

void AAI_Character::LookAtWaypoints(float TimeBeforeTurn)
{
	if(TimePassed > TimeBeforeTurn && bWhereToLook == false)
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->K2_GetActorLocation(), MarkedPoint));
		bWhereToLook = true;
		TimePassed = 0;
	}
	if(TimePassed > TimeBeforeTurn && bWhereToLook == true)
	{
		SetActorRotation(StartingCharacterRotation);
		bWhereToLook = false;
		TimePassed = 0;
	}
}

void AAI_Character::Attacking()
{
	PrintAction("Attacking", 0);
}

void AAI_Character::Roaming()
{
	PrintAction("Roaming", 0);
	ComeAndGo(true, (FMath::RandRange(1, 4)), FVector(1, 0, 0));
}

void AAI_Character::ComeAndGo( bool RandomDirection, float TimeBeforeTurn, FVector MoveDirection)
{
	if(TimePassed > TimeBeforeTurn)
	{
		Direction = Direction * -1;
		TimePassed = 0;
		if (RandomizeDirection == true)
		{
			//Direction = MoveDirection;
			Direction = FVector(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), 0);
		}
	}
	AddMovementInput(Direction, 1);
}

void AAI_Character::PrintAction(FString ActionToPrint, float Duration)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s is %s"), *UKismetSystemLibrary::GetDisplayName(this), *ActionToPrint), true, true, FColor::Green, Duration);
}

void AAI_Character::IncreaseHealth(float Health)
{
	S_AIData.Health += Health;
	PrintAction(FString::Printf(TEXT("healing = %f"), S_AIData.Health), 0);
}

void AAI_Character::SetHealthState()
{
	if(S_AIData.Health >= 60)
	{
		E_AIHealthState = EHealthState::FullHealth;
		return;
	}
	else{}
	if(S_AIData.Health <= 0)
	{
		E_AIHealthState = EHealthState::Dead;
		return;
	}
	else
	if(S_AIData.Health <= 30)
	{
		E_AIHealthState = EHealthState::Endangered;
		return;
	}	
	else
	if(S_AIData.Health < 60)
	{
		E_AIHealthState = EHealthState::Recovery;
		return;
	}	
}

void AAI_Character::HandleDamageSphereHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* playerCharacter = Cast<AMyCPPCharacter>(OtherActor);
	if (IsValid(playerCharacter))
	{
		playerCharacter->HandleDamage(10);
	}	
}

void AAI_Character::OnMovementFinished()
{
	TimePassed = 0;
	//PrintAction(FString::Printf(TEXT("MOVEMENT FINISHED")), 0);
}

void AAI_Character::InteractionAction_Implementation()
{
	// Your implementation here
	UE_LOG(LogTemp, Warning, TEXT("InteractionAction called from AI_Character"));
}

