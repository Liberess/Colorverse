// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "SlimeAIController.h"
#include "ColorverseCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ColorverseCharacter = Cast<AColorverseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ColorverseCharacter)
		return EBTNodeResult::Failed;

	ColorverseCharacter->Attack();

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto ColorverseCharacter = Cast<AColorverseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ColorverseCharacter->GetIsAttacking())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}