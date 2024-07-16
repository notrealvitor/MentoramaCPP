// Fill out your copyright notice in the Description page of Project Settings.


#include "NotPlayerProperties.h"


UNotPlayerProperties::UNotPlayerProperties()
{
	// Initialize your variables here if necessary
	TotalMapTime = 0.0f;
	FailContext = 0;
	MapResource = 0;
	TotalCurrency = 0;
	CurrentCurrency = 0;
	CurrentRound = 0;
	Health = 100;
}

void UNotPlayerProperties::PostInitProperties()
{
	Super::PostInitProperties();

	
	// Initialize any properties or do any setup here after all properties have been initialized
}

