// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem.h"

UCombatSystem::UCombatSystem() : ATK(10), ColorBuff(ATK / 2), ElementBuff(ATK / 2), MaxCombo(3), CurrentCombo(0), bCanNextCombo(false), bIsComboInputOn(false), bIsCanAttackTrace(false)
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

void UCombatSystem::SetColorBuff()
{
	if (GetCurrentPaintColorAmount() >= 5)
	{
		bIsOnColor = true;
	}
	else
	{
		bIsOnColor = false;
	}
}

void UCombatSystem::SetElementBuff(bool value)
{
	bIsOnElement = value;
}

float UCombatSystem::GetCurrentATK()
{
	float CurrnetATK = ATK;

	if (bIsOnColor)
		CurrnetATK += ColorBuff;

	if (bIsOnElement)
		CurrnetATK += ElementBuff;

	return CurrnetATK;
}

float UCombatSystem::GetCurrentPaintColorAmount()
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	float colorAmount = temp->PaintAmountArray[(int)CurrentPaintColor];
	return colorAmount;
}

void UCombatSystem::SetCurrentPaintColorAmount(float value)
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	temp->PaintAmountArray[(int)CurrentPaintColor] += value;

	if (temp->PaintAmountArray[(int)CurrentPaintColor] <= 0.0f)
	{
		temp->PaintAmountArray[(int)CurrentPaintColor] = 0;
	}
	else if (temp->PaintAmountArray[(int)CurrentPaintColor] < 5.0f)
	{
		SetColorBuff();
	}
	
	temp->GetHUDWidget()->SetPaintBarPercent((int)CurrentPaintColor, temp->PaintAmountArray[(int)CurrentPaintColor]);
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

