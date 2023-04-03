// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShotBullet.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API UBTTask_ShotBullet : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ShotBullet();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

	FORCEINLINE void SetIsAttackingFalse() { IsAttacking = false; }
};