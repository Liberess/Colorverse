// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsStartAttack.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API UBTDecorator_IsStartAttack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsStartAttack();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
