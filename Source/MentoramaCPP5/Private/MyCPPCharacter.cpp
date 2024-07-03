// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCPPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyCppBaseMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyCPPCharacter::AMyCPPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AMyCPPCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMyCPPCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTrace(false);
}

void AMyCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCPPCharacter::StunnableJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCPPCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCPPCharacter::Look);
		//This is being handled in the StealthChar BP
		//EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyCPPCharacter::Interact); 
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyCPPCharacter::Move(const FInputActionValue& Value)
{
	if (!bIsStunned)
	{
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr && !AbilityPlaying)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}				
	}
}

void AMyCPPCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyCPPCharacter::AimTrace(bool Debug)
{	
	FVector StartLocation;
	FRotator Direction;
	GetController()->GetPlayerViewPoint(StartLocation, Direction);

	StartLocation = StartLocation +  Direction.Vector() * FVector::Dist(GetActorLocation(), StartLocation);
	FVector EndTraceController = StartLocation + Direction.Vector() * TraceRange;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	bTraceIsHit = GetWorld()->LineTraceSingleByChannel(TraceResult, StartLocation, EndTraceController, ECollisionChannel::ECC_WorldDynamic, queryParams);

	//set the InteractingObject
	if (bTraceIsHit && TraceResult.GetActor()->Implements<UInteractions>())
	{
		if (CurrentInteractable.GetObject() != TraceResult.GetActor() )
		{
			CurrentInteractable = TraceResult.GetActor();
			OnCurrentInteractionsChanged.Broadcast(CurrentInteractable);
		}
	}
	else if (CurrentInteractable.GetObject()) //does it have to have a IsValid or it is enought like this
	{
		CurrentInteractable = nullptr;
		OnCurrentInteractionsChanged.Broadcast(CurrentInteractable);
	}
	
	// Draw debug line to visualize the trace
	if (Debug)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndTraceController, FColor::Yellow, false, 1, 0, 2);
	}
}

void AMyCPPCharacter::Interact() 
{
	if (!AbilityPlaying)
	{
		if (bTraceIsHit && TraceResult.GetActor()->Implements<UInteractions>())
		{
			IInteractions::Execute_InteractionAction(CurrentInteractable.GetObject(), this, SelectedItemSlot); //sends the message to the interacted actor
			InteractionSuccessful();  //this sends a message to this characters BP that the event was successful
		}
	}
}

USceneComponent* AMyCPPCharacter::GetCamera() const
{
	return FollowCamera;
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


void AMyCPPCharacter::StunnableJump()
{
	if (!bIsStunned)
	{
		Jump();
	}
}