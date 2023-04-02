// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "SlimeAIController.h"
#include "ColorverseCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ColorverseCharacter = Cast<AColorverseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ColorverseCharacter)
		return EBTNodeResult::Failed;

	ColorverseCharacter->Attack();
	IsAttacking = true;

	ColorverseCharacter->GetColorverseAnim()->OnEndAttackJudg.AddDynamic(this, &UBTTask_Attack::SetIsAttackingFalse);

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}