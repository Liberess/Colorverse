// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShotBullet.h"
#include "SpiritAIContorller.h"
#include "ColorverseSpirit.h"

UBTTask_ShotBullet::UBTTask_ShotBullet()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_ShotBullet::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ColorverseSpirit = Cast<AColorverseSpirit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ColorverseSpirit)
	{
		return EBTNodeResult::Failed;
	}

	ColorverseSpirit->Attack();
	IsAttacking = true;

	return EBTNodeResult::InProgress;
}

void UBTTask_ShotBullet::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

