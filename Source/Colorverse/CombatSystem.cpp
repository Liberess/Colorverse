#include "CombatSystem.h"

UCombatSystem::UCombatSystem() : ATK(10), ColorBuff(ATK / 2), ElementBuff(ATK / 2), MaxCombo(3), CurrentCombo(0), bCanNextCombo(false), bIsCanInput(true), bIsCanAttackTrace(false)
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	bIsOnElements.Init(false, 3);
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
	if (CurrentPaintColor != ECombineColors::Empty && GetCurrentPaintColorAmount() >= 5)
	{
		bIsOnColor = true;
	}
	else
	{
		bIsOnColor = false;
	}
}

void UCombatSystem::SetElementBuff(int color)
{
	bIsOnElements[color] = true;
}

float UCombatSystem::GetCurrentATK()
{
	float CurrnetATK = ATK;

	if (bIsOnColor)
	{
		CurrnetATK += ColorBuff;

		if (bIsOnElements[(int)CurrentPaintColor])
		{
			CurrnetATK += ElementBuff;
		}
	}

	return CurrnetATK;
}

float UCombatSystem::GetCurrentPaintColorAmount()
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	if(temp != nullptr)
		return temp->PaintAmount;
	return -1.0f;
}

void UCombatSystem::SetCurrentPaintColorAmount(float value)
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	if(temp != nullptr)
	{
		temp->PaintAmount += value;

		if(temp->PaintAmount >= temp->MaxPaintAmount)
			temp->PaintAmount = temp->MaxPaintAmount;
		else if(temp->PaintAmount <= 0.0f)
			temp->PaintAmount = 0.0f;

		if (temp->PaintAmount < 5.0f)
			SetColorBuff();
	}
}

void UCombatSystem::AttackStartComboState()
{
	bIsCanInput = false;
	bCanNextCombo = true;
	CurrentCombo = CurrentCombo + 1;

	if (CurrentCombo > MaxCombo)
	{
		bCanNextCombo = false;
	}
}

void UCombatSystem::AttackEndComboState()
{
	bIsCanInput = true;
	bCanNextCombo = false;
	bIsCanAttackTrace = false;
	CurrentCombo = 0;
}
