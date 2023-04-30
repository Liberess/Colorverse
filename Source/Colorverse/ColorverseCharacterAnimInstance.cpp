// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorverseCharacterAnimInstance.h"
#include "ColorverseCharacter.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Blue, text);

UColorverseCharacterAnimInstance::UColorverseCharacterAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_MONTAGE(TEXT("/Game/Animations/Anim_Warrior_Attack_Montage"));
	if (Attack_MONTAGE.Succeeded())
	{
		AttackMontage = Attack_MONTAGE.Object;
	}
}

void UColorverseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

}

void UColorverseCharacterAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UColorverseCharacterAnimInstance::PlayJumpAttackMontage()
{
	if (!Montage_IsPlaying(JumpAttackMontage))
	{
		Montage_Play(JumpAttackMontage, 1.0f);
	}
}

void UColorverseCharacterAnimInstance::PlayDamagedMontage()
{
	if (!Montage_IsPlaying(DamagedMontage))
	{
		Montage_Play(DamagedMontage, 1.0f);
	}
}

void UColorverseCharacterAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UColorverseCharacterAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UColorverseCharacterAnimInstance::AnimNotify_StartAttackJudg()
{
	OnStartAttackJudg.Broadcast();
}

void UColorverseCharacterAnimInstance::AnimNotify_EndAttackJudg()
{
	OnEndAttackJudg.Broadcast();
}

void UColorverseCharacterAnimInstance::AnimNotify_EndAttack()
{
	OnEndAttack.Broadcast();
}

void UColorverseCharacterAnimInstance::AnimNotify_EndDamaged()
{
	OnEndDamaged.Broadcast();
}

FName UColorverseCharacterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}