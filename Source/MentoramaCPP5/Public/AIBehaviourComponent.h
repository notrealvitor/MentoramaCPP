// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI_Character.h"

#include "AIBehaviourComponent.generated.h"

UENUM(BlueprintType)
enum EState
{
	Idle,
	Attacking,
	Roaming,
	PatrolWaypoints,
	LookAtWaypoints
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MENTORAMACPP5_API UAIBehaviourComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UAIBehaviourComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//ACharacter* ComponentOwner = nullptr;

	UFUNCTION(BlueprintCallable)
	void EnemyBehaviour(float DeltaTime);

	//UFUNCTION(BlueprintCallable)
	//void Idle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EState> E_AIState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CharacterSpeed = 200;
	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeBeforeTurn = 3;
	
	AAI_Character* OwnerAICharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAlive = true;


};
