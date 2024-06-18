// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MentoramaCPP5Character.h"
#include "MyMentoramaCPP5AI.generated.h"

class UAIBehaviourComponent;

UENUM(BlueprintType)
enum EAIHealthState
{
	FullHealthState,
	RecoveryState,
	EndangeredState,
	DeadState
};

USTRUCT(BlueprintType)
struct FAIEnemyData    //I want to make a Attributes or CharacterStatus Component to control those things
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name = "Ai Guy";
};

UCLASS()
class MENTORAMACPP5_API AMyMentoramaCPP5AI : public AMentoramaCPP5Character
{
	GENERATED_BODY()

public:
	AMyMentoramaCPP5AI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAIBehaviourComponent* AIBehaviourComp;

	//TEnumAsByte<EAIHealthState> E_AIHealthState;
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//FAIEnemyData S_AIData;
	
};
