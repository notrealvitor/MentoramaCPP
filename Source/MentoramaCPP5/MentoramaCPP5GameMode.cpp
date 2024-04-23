// Copyright Epic Games, Inc. All Rights Reserved.

#include "MentoramaCPP5GameMode.h"
#include "MentoramaCPP5Character.h"
#include "UObject/ConstructorHelpers.h"

AMentoramaCPP5GameMode::AMentoramaCPP5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
