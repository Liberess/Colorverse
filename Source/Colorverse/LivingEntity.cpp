#include "LivingEntity.h"

ULivingEntity::ULivingEntity()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULivingEntity::BeginPlay()
{
	Super::BeginPlay();
}

void ULivingEntity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULivingEntity::ApplyDamage_Implementation(FDamageMessage dmgMsg)
{
	//IIDamageable::ApplyDamage_Implementation(dmgMsg);
	
}

