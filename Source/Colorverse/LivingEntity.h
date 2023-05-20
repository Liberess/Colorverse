#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "Components/ActorComponent.h"
#include "LivingEntity.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLORVERSE_API ULivingEntity : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULivingEntity();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LivingEntity|Damageable")
	void ApplyDamage(FDamageMessage dmgMsg);
	
	UFUNCTION(BlueprintCallable, Category = "LivingEntity|HealthPoint")
	void CureHealth(int CureAmount);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LivingEntity|HealthPoint")
	int OriginHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LivingEntity|HealthPoint")
	int CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "LivingEntity|HealthPoint")
	bool GetDead() const { return bIsDead;}

	UFUNCTION(BlueprintCallable, Category = "LivingEntity|HealthPoint")
	void SetDead(bool value) { bIsDead = value; }

private:
	bool bIsDead;

	//공격 허용 딜레이
	const float MinTimeBetweenDamaged = 0.1f;

	//마지막으로 공격 당한 시간
	float LastDamagedTime;
};
