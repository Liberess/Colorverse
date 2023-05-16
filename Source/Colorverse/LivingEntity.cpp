#include "LivingEntity.h"

ULivingEntity::ULivingEntity() : OriginHealth(100), CurrentHealth(OriginHealth)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULivingEntity::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = OriginHealth;
}

void ULivingEntity::ApplyDamage_Implementation(FDamageMessage dmgMsg)
{
	CurrentHealth -= dmgMsg.damageAmount;

	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}
