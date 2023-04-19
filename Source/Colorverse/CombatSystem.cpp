#include "CombatSystem.h"

UCombatSystem::UCombatSystem() : ATK(10), ColorBuff(ATK / 2), ElementBuff(ATK / 2), MaxCombo(3), CurrentCombo(0), bCanNextCombo(false), bIsComboInputOn(false), bIsCanAttackTrace(false)
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
	if (GetCurrentPaintColorAmount() >= 5)
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
	return temp->PaintAmount;
}

void UCombatSystem::SetCurrentPaintColorAmount(float value)
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	temp->PaintAmount += value;

	if (temp->PaintAmount <= 0.0f)
	{
		temp->PaintAmount = 0;
	}
	else if (temp->PaintAmount < 5.0f)
	{
		SetColorBuff();
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
		FString::Printf(TEXT("%f"), temp->PaintAmount));
	temp->GetHUDWidget()->SetPaintBarPercent(temp->PaintAmount);
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

