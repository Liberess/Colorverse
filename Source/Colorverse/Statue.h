#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "Statue.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AStatue : public AInteractObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bIsUnlock = false;

protected:
	virtual void BeginPlay() override;

public:
	AStatue();
	virtual void OnEnter() override;
	virtual void OnInteract() override;
	virtual void OnExit() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpenInventoryByStatue;
};
