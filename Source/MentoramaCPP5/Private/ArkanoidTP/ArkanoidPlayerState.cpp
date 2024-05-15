// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidTP/ArkanoidPlayerState.h"

void AArkanoidPlayerState::BeginPlay()
{
	Super::BeginPlay();
	Lives = StartingLives;
}
