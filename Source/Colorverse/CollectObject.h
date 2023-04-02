#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "IItem.h"
#include "InteractObject.h"
#include "CollectObject.generated.h"

UCLASS()
class COLORVERSE_API ACollectObject : public AInteractObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object", meta=(AllowPrivateAccess))
	int ItemID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object", meta=(AllowPrivateAccess))
	ECollectType CollectType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Collect Object",meta=(AllowPrivateAccess))
	FItem ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collect Object",meta=(AllowPrivateAccess))
	UDataTable* ItemDataTable;
	
	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

public:
	ACollectObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int PaintedCount = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int NeedsPaintedCount = 3;
};
