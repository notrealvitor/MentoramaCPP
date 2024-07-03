#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

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

    // // Function to update stats based on level and equipment, I think it would get the equipment from the EquipmentComponent and refresh all this info, if the component is not present then just ignore and use default values
    // UFUNCTION(BlueprintCallable, Category="Stats")
    // void UpdateStats(int32 NewLevel, const TArray<class AEquipment*>& Equipment);

    //Ideally hose values should not be set manually but only by its functions, for example: current Health should be only Handled by Damage or Heal.
    // Attributes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Health = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float MaxHealth = 100;
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
    float Mana = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float MaxMana = 50;    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    int32 Experience;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    int32 Level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Luck;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
    float Defense;
    
};