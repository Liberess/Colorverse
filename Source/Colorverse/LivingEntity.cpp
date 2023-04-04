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

void ULivingEntity::ApplyDamage(FDamageMessage dmgMsg)
{
	float temp = CurrentHealth;

	CurrentHealth -= dmgMsg.damageAmount;
}