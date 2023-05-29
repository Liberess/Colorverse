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
	return temp->GetPaintAmount();
}

void UCombatSystem::SetCurrentPaintColorAmount(float value)
{
	UInventoryManager* temp = GetWorld()->GetSubsystem<UInventoryManager>();
	temp->CurePaint(value);

	if (temp->GetPaintAmount() < 5.0f)
		SetColorBuff();
	
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%f"), temp->PaintAmount));
	temp->GetHUDWidget()->SetPaintBarPercent(temp->GetPaintAmount());
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

