// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NotPlayerProperties.h"
#include "MentoramaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API UMentoramaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
	UPROPERTY(BlueprintReadWrite, Transient)
	UNotPlayerProperties* VM_NotPlayerProperties;

	UPROPERTY(BlueprintReadWrite)
	int StartingLives = 77;
	
};
