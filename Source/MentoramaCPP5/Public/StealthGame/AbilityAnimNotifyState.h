#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AbilityAnimNotifyState.generated.h"

class UItemAbility;

UCLASS()
class MENTORAMACPP5_API UAbilityAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UItemAbility* ItemAbilityOwner;
	
};
