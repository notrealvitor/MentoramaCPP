// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MoveUntilFindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API UBTT_MoveUntilFindPlayer : public UBTTask_BlackboardBase //UBTTaskNode //
{
	GENERATED_BODY()

public:
	UBTT_MoveUntilFindPlayer(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector ActorToFollowKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector MovingTaskKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector IsCharacterVisibleKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AcceptanceRadius = 5.0f;

private:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
