// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ColorverseCharacterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndAttackJudgDelegate);

UCLASS()
class COLORVERSE_API UColorverseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UColorverseCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

public:
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnEndAttackJudgDelegate OnStartAttackJudg;
	FOnEndAttackJudgDelegate OnEndAttackJudg;

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_StartAttackJudg();

	UFUNCTION()
	void AnimNotify_EndAttackJudg();

	FName GetAttackMontageSectionName(int32 Section);
};
