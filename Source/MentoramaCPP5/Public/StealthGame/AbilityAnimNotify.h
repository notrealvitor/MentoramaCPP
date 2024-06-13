#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AbilityAnimNotify.generated.h"

class UItemAbility;

UCLASS()
class MENTORAMACPP5_API UAbilityAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UItemAbility* ItemAbilityOwner;
};
