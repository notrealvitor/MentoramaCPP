#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MENTORAMACPP5_API UCharacterStatsComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UCharacterStatsComponent();
    // Called when the game starts
    virtual void BeginPlay() override;

public:
   // Functions to manage life and death
    UFUNCTION(BlueprintCallable, Category="Stats")
    void TakeDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category="Stats")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category="Stats")
    void Die();

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category="Stats")
    FOnDeath OnDeath;

    UFUNCTION(BlueprintCallable, Category="Stats")
    void CalculateStats();

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category="Stats")
    FOnHealthChanged OnHealthChanged;

    // // Function to update stats based on level and equipment, I think it would get the equipment from the EquipmentComponent and refresh all this info, if the component is not present then just ignore and use default values
    // UFUNCTION(BlueprintCallable, Category="Stats")
    // void UpdateStats(int32 NewLevel, const TArray<class AEquipment*>& Equipment);

    //Ideally hose values should not be set manually but only by its functions, for example: current Health should be only Handled by Damage or Heal.
    // Attributes
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Health = 100;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float MaxHealth = 100;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    bool IsAlive;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Strength;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Agility;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Intelligence;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Endurance;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Mana = 50;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float MaxMana = 50;    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    int32 Experience;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    int32 Level;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Luck;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
    float Defense;
    
};