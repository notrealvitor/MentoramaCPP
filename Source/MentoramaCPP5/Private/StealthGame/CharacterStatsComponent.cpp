#include "StealthGame/CharacterStatsComponent.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values
	MaxHealth = 100.0f;
	Health = MaxHealth;
	MaxMana = 50.0f;
	Mana = MaxMana;	
	IsAlive = true;
	Strength = 10.0f;
	Agility = 10.0f;
	Intelligence = 10.0f;
	Endurance = 10.0f;
	Experience = 0;
	Level = 1;
	Luck = 5.0f;
	Defense = 5.0f;
}

void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterStatsComponent::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		Health = 0.0f;
		Die();
	}
	OnHealthChanged.Broadcast();
}

void UCharacterStatsComponent::Heal(float HealAmount)
{
	Health += HealAmount;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
	OnHealthChanged.Broadcast();
}

void UCharacterStatsComponent::Die()
{
	IsAlive = false;
	OnDeath.Broadcast();
	// Handle death logic here (e.g., disable character, play death animation)
}

void UCharacterStatsComponent::CalculateStats()
{
	// Implement your stat calculation logic based on level and other factors
}

// void UCharacterStatsComponent::UpdateStats(int32 NewLevel, const TArray<class AEquipment*>& Equipment)
// {
// 	Level = NewLevel;
// 	// Calculate stats based on level and equipment
// 	CalculateStats();
// }