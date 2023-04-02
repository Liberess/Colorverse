#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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

UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

class COLORVERSE_API IIDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Damageable")
	virtual void ApplyDamage(FDamageMessage dmgMsg) = 0;
};
