// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NotPlayerProperties.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API UNotPlayerProperties : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UNotPlayerProperties();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify)
	float TotalMapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify)
	int FailContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify)
	int MapResource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify)
	int TotalCurrency;

	// Another integer variable with Field Notify
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify)
	int CurrentCurrency;

protected:
	virtual void PostInitProperties() override;
	
};
