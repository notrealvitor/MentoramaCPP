// Fill out your copyright notice in the Description page of Project Settings.


#include "MentoramaGameInstance.h"


void UMentoramaGameInstance::Init()
{
	Super::Init();
	VM_NotPlayerProperties = NewObject<UNotPlayerProperties>(this, UNotPlayerProperties::StaticClass());
	VM_NotPlayerProperties->SetFailContext(StartingLives);
}

