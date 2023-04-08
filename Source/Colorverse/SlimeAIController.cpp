// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeAIController.h"
#include "ColorverseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName ASlimeAIController::HomePosKey(TEXT("HomePos"));
const FName ASlimeAIController::TargetKey(TEXT("Target"));
const FName ASlimeAIController::HasLineOfSightKey(TEXT("HasLineOfSight"));

ASlimeAIController::ASlimeAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Blueprints/AI/BB_Slime"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Blueprints/AI/BT_Slime"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ASlimeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ASlimeAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

void ASlimeAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}