// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectOwner.h"
#include "ColorverseCharacter.h"
#include "SpiritAIContorller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_DetectOwner::UBTService_DetectOwner()
{
	NodeName = TEXT("DetectOwner");
	Interval = 1.0f;
}

void UBTService_DetectOwner::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World) return;

	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 200.0f;

	// 200�� �������� ���� ��ü�� ���� ������Ʈ�� �����Ѵ�.
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// ������Ʈ�� ������ �Ǹ�, �� ������Ʈ�� Character���� �˻��Ѵ�.
	if (bResult)
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			AColorverseCharacter* ColorverseCharacter = Cast<AColorverseCharacter>(OverlapResult.GetActor());
			if (ColorverseCharacter && ColorverseCharacter->GetController()->IsPlayerController())
			{
				if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASpiritAIContorller::OwnerActorKey) == nullptr)
				{
					// Character��, �����忡 �����Ѵ�.
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASpiritAIContorller::OwnerActorKey, ColorverseCharacter);
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASpiritAIContorller::IsInOwnerSpaceKey, true);

				// ����� ��.
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, ColorverseCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ColorverseCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASpiritAIContorller::IsInOwnerSpaceKey, false);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}