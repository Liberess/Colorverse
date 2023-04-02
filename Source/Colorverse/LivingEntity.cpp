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

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Hp - damaged = Hp : %d - %d = %d"), temp, dmgMsg.damageAmount, CurrentHealth));
}