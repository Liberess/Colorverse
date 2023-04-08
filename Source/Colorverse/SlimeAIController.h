// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SlimeAIController.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API ASlimeAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASlimeAIController();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName HasLineOfSightKey;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
