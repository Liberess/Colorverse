// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsStartAttack.h"
#include "ColorverseCharacter.h"
#include "SpiritAIContorller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <time.h>

UBTDecorator_IsStartAttack::UBTDecorator_IsStartAttack()
{
	NodeName = TEXT("StartAttack");
}

bool UBTDecorator_IsStartAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	AColorverseCharacter* Owner = Cast<AColorverseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASpiritAIContorller::OwnerActorKey));
	TArray<AActor*> AttackHitResults = Owner->AttackHitResults;
	if (AttackHitResults.Num() <= 0)
	{
		return false;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASpiritAIContorller::TargetKey, AttackHitResults[rand() % AttackHitResults.Num()]);
		return true;
	}
}