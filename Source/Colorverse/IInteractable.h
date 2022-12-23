#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UINTERFACE(Blueprintable)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};

class COLORVERSE_API IIInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnEnter() = 0;
	
	UFUNCTION()
	virtual void OnInteract() = 0;
	
	UFUNCTION()
	virtual void OnExit() = 0;
};
