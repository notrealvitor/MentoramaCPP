// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StealthGame/Interactions.h"
#include "GameFramework/Character.h"

#include "AI_Character.generated.h"

 // Forward declaration to avoid circular dependency
class UAIBehaviourComponent;

UENUM(BlueprintType)
enum EHealthState
{
	FullHealth,
	Recovery,
	Endangered,
	Dead
};

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name = "Ai Guy";
};

class Weapon // m7 explicacao
{
public:
	Weapon(); //constructor chamado ao iniciar
	~Weapon(); //destrutor, chamado ao terminar
	int CurrentAmmo;

private:
	const int AmmoMagazine = 30;
};


UCLASS()
class MENTORAMACPP5_API AAI_Character : public ACharacter ,public IInteractions
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TakingDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Idle();

	UFUNCTION(BlueprintCallable)
	void PatrolWaypoints(float TimeBeforeTurn);

	UFUNCTION(BlueprintCallable)
	void LookAtWaypoints(float TimeBeforeTurn);

	UFUNCTION(BlueprintCallable)
	void Attacking();

	UFUNCTION(BlueprintCallable)
	void Roaming();

	UFUNCTION(BlueprintCallable)
	void ComeAndGo(bool RandomDirection, float TimeBeforeTurn, FVector MoveDirection);

	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float Health);

	void SetHealthState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeToTurn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CharacterSpeed = 200;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool RandomizeDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUsePatrolPoint = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (MakeEditWidget = true))
	FVector PatrolPoint;

	FVector StartingCharacterPoint;
	FRotator StartingCharacterRotation;

	UFUNCTION(BlueprintCallable)
	void PrintAction(FString ActionToPrint, float Duration);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FEnemyData S_AIData;

	TEnumAsByte<EHealthState> E_AIHealthState;

	float TimePassed = 1;
	bool bWhereToLook = false;
	

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) //torna possible editar as propriedades mas n os componentes
	class USphereComponent* damageSphere; //a class é um "forward declaration", diz ao compilador que aqui vai ser definido no .cpp, para não precisar colocar include nesse .h, diminui o tempo de compilação e evitar referencias duplicadas

	UFUNCTION()
	void HandleDamageSphereHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMovementFinished();

	FVector MarkedPoint;
	
	UFUNCTION()
	FVector RotateMyVector(const FVector& VectorToRotate, const FRotator& Rotation);

	virtual void InteractionAction_Implementation(AActor* Interactor, UItemSlot* InteractorItem) override; // dont forget to add the public IInteractions into the class call

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAIBehaviourComponent* AIBehaviourComp;

};
