// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "StealthGame/InventoryComponent.h"
#include "NotPlayerProperties.generated.h"


UCLASS()
class MENTORAMACPP5_API UNotPlayerProperties : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UNotPlayerProperties();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	float TotalMapTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int FailContext = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int CurrentRound = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int MapResource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int TotalCurrency;

	// Another integer variable with Field Notify
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	int CurrentCurrency;

	// Another integer variable with Field Notify
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	TArray<FInventorySlot> InventorySlots;

	

protected:
	virtual void PostInitProperties() override;

public:

//TotalMapTime
	void SetTotalMapTime(float NewTotalMapTime)
	{
		UE_MVVM_SET_PROPERTY_VALUE(TotalMapTime, NewTotalMapTime);
	}

	float GetTotalMapTime() const
	{
		return TotalMapTime;
	}
//SetFailContext
	void SetFailContext(int32 NewFailContext)
	{
		UE_MVVM_SET_PROPERTY_VALUE(FailContext, NewFailContext);
	}

	int32 GetFailContext() const
	{
		return FailContext;
	}
//CurrentRound
	void SetCurrentRound(int32 NewCurrentRound)
	{
		UE_MVVM_SET_PROPERTY_VALUE(CurrentRound, NewCurrentRound);
	}

	int32 GetCurrentRound() const
	{
		return CurrentRound;
	}
//map
	void SetMapResource(int32 NewMapResource)
	{
		UE_MVVM_SET_PROPERTY_VALUE(MapResource, NewMapResource);
	}

	int32 GetMapResource() const
	{
		return MapResource;
	}
//TotalCurrency
	void SetTotalCurrency(int32 NewTotalCurrency)
	{
		UE_MVVM_SET_PROPERTY_VALUE(CurrentRound, NewTotalCurrency);
	}

	int32 GetTotalCurrency() const
	{
		return CurrentRound;
	}
//Current Currency
	void SetCurrentCurrency(int32 NewCurrentCurrency)
	{
		UE_MVVM_SET_PROPERTY_VALUE(CurrentCurrency, NewCurrentCurrency);
	}

	int32 GetCurrentCurrency() const
	{
		return CurrentCurrency;
	}

//InventorySlots
	void SetInventorySlots(const TArray<FInventorySlot>& NewInventorySlots)
	{
		UE_MVVM_SET_PROPERTY_VALUE(InventorySlots, NewInventorySlots);
	}

	const TArray<FInventorySlot>& GetInventorySlots() const
	{
		return InventorySlots;
	}
	
};
