// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCppBaseMode.h"

void AMyCppBaseMode::SetPlayerIsDead()
{
	OnMyGameOver.Broadcast();
}

void AMyCppBaseMode::RegisterObjective()
{
	ObjectivesCount++;
}

void AMyCppBaseMode::UnregisterObjective()
{
		if(HasGameEnded) return;
		ObjectivesCount--;
		if(ObjectivesCount <= 0 )
		{
			OnMyGameWon.Broadcast();
			HasGameEnded = true;
		}
}
