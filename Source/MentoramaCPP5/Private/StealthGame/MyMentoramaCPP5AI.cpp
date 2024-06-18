// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/MyMentoramaCPP5AI.h"

#include "AIBehaviourComponent.h"


AMyMentoramaCPP5AI::AMyMentoramaCPP5AI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the custom component and attach it to the actor
	AIBehaviourComp = CreateDefaultSubobject<UAIBehaviourComponent>(TEXT("AIBehaviourComponent"));
	AddOwnedComponent(AIBehaviourComp);
}
