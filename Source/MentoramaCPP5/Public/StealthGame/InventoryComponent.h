// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "GameFramework/Actor.h"
#include "InventoryComponent.generated.h"

class UNotPlayerProperties;

class UItemSlot;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UItemSlot* ItemSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Amount;
	
	bool operator==(const FInventorySlot& Other) const
	{
		// Ensure both ItemSlot pointers are either null or point to the same object and amounts are equal
		return (ItemSlot == Other.ItemSlot) && (Amount == Other.Amount);
	}
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MENTORAMACPP5_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	TArray<FInventorySlot> Slots;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int NumberOfSlots = 8;

	UFUNCTION(BlueprintPure)
	const FORCEINLINE FInventorySlot& GetSlot(int Index) const
	{
		//checkf(Slots.Num() > Index, TEXT("Tried to access index out of bounds")); // this is a crash message example
		return Slots[Index];
	};

	const FORCEINLINE UItemSlot* GetItem(int Index) const
	{
		return GetSlot(Index).ItemSlot;
	};

	FORCEINLINE int GetAmount(int Index) const
	{
		return GetSlot(Index).Amount;
	};

	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(UItemSlot* ItemSlot, int Amount);

	UFUNCTION(BlueprintCallable)
	bool SwapSlotItems(UItemSlot* InvFrom, int IndexSlotFrom, int AmountFrom, UItemSlot* InvTo, int IndexSlotTo, int AmountTo);

	UFUNCTION(BlueprintCallable)
	void ClearSlot(int Index);

	UPROPERTY(BlueprintReadOnly)
	UNotPlayerProperties* VM_NotPlayerProperties;

	UFUNCTION(BlueprintCallable)
	bool SetSlot(int Index, UItemSlot* ItemSlot, int Amount);

	UFUNCTION(BlueprintCallable)
	void UpdateVisualModel();
};
