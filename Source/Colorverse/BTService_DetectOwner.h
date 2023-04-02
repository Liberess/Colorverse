// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectOwner.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API UBTService_DetectOwner : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_DetectOwner();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
