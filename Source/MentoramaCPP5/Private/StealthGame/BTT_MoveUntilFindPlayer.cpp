// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGame/BTT_MoveUntilFindPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tasks/AITask_MoveTo.h"


UBTT_MoveUntilFindPlayer::UBTT_MoveUntilFindPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = true;
}

void UBTT_MoveUntilFindPlayer::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTT_MoveUntilFindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Controller = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		const auto Character = Controller->GetPawn();
		const auto Blackboard = Controller->GetBlackboardComponent();
		if (Blackboard)
		{
			const auto ActorToFollow = Cast<AActor>(Blackboard->GetValueAsObject(ActorToFollowKey.SelectedKeyName));
			if (ActorToFollow)
			{
				Controller->MoveToActor(ActorToFollow, AcceptanceRadius);
				return EBTNodeResult::InProgress;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ActorToFollow is null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Blackboard is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is null"));
	}

	return EBTNodeResult::Failed;
}

void UBTT_MoveUntilFindPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard is null"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!Blackboard->GetValueAsBool(IsCharacterVisibleKey.SelectedKeyName))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (const auto Controller = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		const auto ActorToFollow = Cast<AActor>(Blackboard->GetValueAsObject(ActorToFollowKey.SelectedKeyName));
		const auto Pawn = Controller->GetPawn();

		if (ActorToFollow && Pawn)
		{
			if (ActorToFollow->GetDistanceTo(Pawn) <= AcceptanceRadius)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return;
			}

			if (Pawn->GetVelocity().Size() == 0)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				return;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ActorToFollow or Pawn is null"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is null"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}

