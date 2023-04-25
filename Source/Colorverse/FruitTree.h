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

	UPROPERTY(BlueprintReadOnly, Category="Fruit Tree", meta=(AllowPrivateAccess))
	TArray<FTimerHandle> SpawnTimerHandles;

public:
	AFruitTree();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fruit Tree")
	float SpawnDelayTime = 3.0f;

	UFUNCTION(BlueprintCallable)
	void SetActiveCollectObject(bool active, int index);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Fruit Tree")
	TArray<ACollectObject*> CollectObjects;
};
