// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/InventoryComponent.h"
#include "MentoramaGameInstance.h"
#include "ContentBrowserDataSource.h"
#include "IDetailTreeNode.h"
#include "Math/UnitConversion.h"
#include "StealthGame/ItemSlot.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Slots.Init(FInventorySlot(), NumberOfSlots);

	//Getting the VM from the game instance
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UMentoramaGameInstance* MyMentoramaGameInstance = Cast<UMentoramaGameInstance>(GameInstance);
	
	if (MyMentoramaGameInstance)
	{
		VM_NotPlayerProperties = MyMentoramaGameInstance->VM_NotPlayerProperties;
		UpdateVisualModel();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("VM_NotPlayerProperties not found!"));
	}
	
}

bool UInventoryComponent::AddItemToInventory(UItemSlot* ItemSlot, int Amount)
{
	if (!ItemSlot) return false;
	if (Amount <= 0) return false;

	for (int i = 0; i < NumberOfSlots; i++)
	{
		if (Slots[i].Amount == 0 || Slots[i].ItemSlot == ItemSlot)
		{
		Slots[i].Amount += Amount;
		Slots[i].ItemSlot = ItemSlot;
		
		VM_NotPlayerProperties->SetInventorySlots(Slots); //does not need the broadcast since the MVVM do this auto
		return true;
		};
	}
	return false;
}

bool UInventoryComponent::SwapSlotItems(UItemSlot* InvFrom, int IndexSlotFrom, int AmountFrom, UItemSlot* InvTo, int IndexSlotTo, int AmountTo)
{
	if (!InvFrom && !InvTo) return false;
	if (InvFrom == InvTo && IndexSlotFrom == IndexSlotTo) return false;
	
	//const auto& SlotFrom = InvFrom->GetSlot(IndexSlotFrom);
	//if(!InvTo->SetSlot(IndexSlotTo, SlotFrom.ItemSlot, SlotFrom.Amount)) return false;
	UItemSlot* SaveInvTo = InvTo;
	UItemSlot* SaveInvFrom = InvFrom;
	SetSlot(IndexSlotTo, SaveInvFrom, AmountFrom);
	SetSlot(IndexSlotFrom, SaveInvTo, AmountTo);
	
	//UE_LOG(LogTemp, Error, TEXT("PrintingSlots To: %d, %s, %d"),IndexSlotTo, *InvTo->GetName(), AmountTo);
	//UE_LOG(LogTemp, Error, TEXT("PrintingSlots From: %d, %s, %d"),IndexSlotFrom, *InvFrom->GetName(), AmountFrom);
	
	UpdateVisualModel();

	return true;
}

void UInventoryComponent::ClearSlot(int Index)
{
	Slots[Index].Amount = 0;
	Slots[Index].ItemSlot = nullptr;
}

bool UInventoryComponent::SetSlot(int Index, UItemSlot* ItemSlot, int Amount)
{
	//if (Slots[Index].Amount > 0) return false;
	//if (Amount <= 0) return false;
	//if (!ItemSlot) return false;

	Slots[Index].Amount = Amount;
	Slots[Index].ItemSlot = ItemSlot;
	return true;
}

void UInventoryComponent::UpdateVisualModel() //updates the visual model with the local reference
{
	VM_NotPlayerProperties->SetInventorySlots(Slots);
}


