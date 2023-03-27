#include "LivingEntity.h"

ULivingEntity::ULivingEntity()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULivingEntity::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = OriginHealth;
}

void ULivingEntity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULivingEntity::ApplyDamage_Implementation(FDamageMessage dmgMsg)
{
	CurrentHealth -= dmgMsg.damageAmount;

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("HP : %d"), CurrentHealth));
}

