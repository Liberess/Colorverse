// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem.h"

UCombatSystem::UCombatSystem() : MaxCombo(3), CurrentCombo(0), bCanNextCombo(false), bIsComboInputOn(false), bIsCanAttackTrace(false)
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCombatSystem::BeginPlay()
{
	Super::BeginPlay();

	AttackEndComboState();
}

void UCombatSystem::InitializeComponent()
{
	Super::InitializeComponent();
}

void UCombatSystem::AttackStartComboState()
{
	bIsComboInputOn = false;
	bCanNextCombo = true;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);

	if (CurrentCombo == MaxCombo)
	{
		bCanNextCombo = false;
	}
}

void UCombatSystem::AttackEndComboState()
{
	bIsComboInputOn = false;
	bCanNextCombo = false;
	bIsCanAttackTrace = false;
	CurrentCombo = 0;
}

