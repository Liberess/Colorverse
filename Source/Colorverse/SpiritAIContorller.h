// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpiritAIContorller.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API ASpiritAIContorller : public AAIController
{
	GENERATED_BODY()

public:
	ASpiritAIContorller();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	static const FName OwnerActorKey;
	static const FName TargetKey;
	static const FName IsInOwnerSpaceKey;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
