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

	UFUNCTION(BlueprintCallable)
	void RunAI();

	UFUNCTION(BlueprintCallable)
	void StopAI();

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName HasLineOfSightKey;

	static const FName IsNearRangeKey;
	static const FName IsMiddleRangeKey;
	static const FName IsFarRangeKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TArray <float> Ranges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int SkillNum;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UBlackboardData* BBAsset;
};
