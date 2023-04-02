// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritAIContorller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName ASpiritAIContorller::OwnerActorKey(TEXT("OwnerActor"));
const FName ASpiritAIContorller::TargetKey(TEXT("Target"));
const FName ASpiritAIContorller::IsInOwnerSpaceKey(TEXT("IsInOwnerSpace"));

ASpiritAIContorller::ASpiritAIContorller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Blueprints/AI/BB_Spirit"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Blueprints/AI/BT_Spirit"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ASpiritAIContorller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ASpiritAIContorller::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

void ASpiritAIContorller::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}