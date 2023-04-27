#pragma once

#include "CoreMinimal.h"
#include "CollectObject.h"
#include "IItem.h"
#include "InteractObject.h"
#include "FruitTree.generated.h"

UCLASS(BlueprintType, Blueprintable)
class COLORVERSE_API AFruitTree : public AInteractObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="Fruit Tree", meta=(AllowPrivateAccess))
	UDataTable* ItemDT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Fruit Tree", meta=(AllowPrivateAccess))
	FItem ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Fruit Tree", meta=(AllowPrivateAccess))
	FItem WoodStickData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fruit Tree", meta=(AllowPrivateAccess))
	int ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fruit Tree", meta=(AllowPrivateAccess))
	int MaxWoodStickAcquireAmount = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Fruit Tree", meta=(AllowPrivateAccess))
	bool CanAcquireFruit = true;
	
	UPROPERTY(BlueprintReadOnly, Category="Fruit Tree", meta=(AllowPrivateAccess))
	FTimerHandle SpawnTimerHandle;

public:
	AFruitTree();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fruit Tree")
	float FruitSpawnDelayTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fruit Tree")
	float FruitGlownVelocity = 2.0f;

	UFUNCTION(BlueprintCallable)
	void SetActiveCollectObject(bool active);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Fruit Tree")
	TArray<ACollectObject*> CollectObjects;
};
