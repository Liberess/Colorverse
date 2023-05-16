// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "ColorverseCharacter.h"
#include "SlimeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AColorverseCharacter* ColorverseCharacter = Cast<AColorverseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASlimeAIController::TargetKey));
	ASlimeAIController* controller = Cast<ASlimeAIController>(OwnerComp.GetAIOwner());
	AColorverseCharacter* owner = Cast<AColorverseCharacter>(controller->GetPawn());

	if (owner->GetIsAttacking())
		return;

	if (IsValid(ColorverseCharacter))
	{
		float distance = owner->GetDistanceTo(ColorverseCharacter);

		if (distance > controller->Ranges[2])
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsFarRangeKey, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsMiddleRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsNearRangeKey, false);

			controller->SkillNum = 0;
		}
		else if (distance > controller->Ranges[1])
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsFarRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsMiddleRangeKey, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsNearRangeKey, false);

			controller->SkillNum = 1;
		}
		else if (distance > controller->Ranges[0])
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsFarRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsMiddleRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsNearRangeKey, true);

			controller->SkillNum = 2;
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsFarRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsMiddleRangeKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASlimeAIController::IsNearRangeKey, false);
		}
	}
}