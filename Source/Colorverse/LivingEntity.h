#pragma once

#include "CoreMinimal.h"
#include "IDamageable.h"
#include "Components/ActorComponent.h"
#include "LivingEntity.generated.h"

UCLASS()
class COLORVERSE_API ULivingEntity : public UActorComponent, public IIDamageable
{
	GENERATED_BODY()

public:	
	ULivingEntity();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ApplyDamage_Implementation(FDamageMessage dmgMsg) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Living Entity")
	int OriginHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Living Entity")
	int CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "Living Entity")
	bool GetDead() const { return bIsDead;}

	UFUNCTION(BlueprintCallable, Category = "Living Entity")
	void SetDead(bool value) { bIsDead = value; }

private:
	bool bIsDead;

	//공격 허용 딜레이
	const float MinTimeBetweenDamaged = 0.1f;

	//마지막으로 공격 당한 시간
	float LastDamagedTime;
};
