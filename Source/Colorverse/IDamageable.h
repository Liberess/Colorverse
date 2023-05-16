#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamageable.generated.h"

USTRUCT(BlueprintType)
struct FDamageMessage
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Message")
	AActor* damager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Message")
	float damageAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Message")
	FVector hitPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Message")
	FVector hitNormal;
};