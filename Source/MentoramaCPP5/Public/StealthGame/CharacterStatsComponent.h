#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MENTORAMACPP5_API UCharacterStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UCharacterStatsComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Attributes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    bool IsAlive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Strength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Agility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Intelligence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Endurance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Mana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float MaxMana;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    int32 Experience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Luck;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Defense;

    // Functions to manage life and death
    UFUNCTION(BlueprintCallable, Category="Stats")
    void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category="Stats")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category="Stats")
    void Die();

    UFUNCTION(BlueprintCallable, Category="Stats")
    void CalculateStats();

    // // Function to update stats based on level and equipment, I think it would get the equipment from the EquipmentComponent and refresh all this info, if the component is not present then just ignore and use default values
    // UFUNCTION(BlueprintCallable, Category="Stats")
    // void UpdateStats(int32 NewLevel, const TArray<class AEquipment*>& Equipment);
};