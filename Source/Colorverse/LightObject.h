#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "GameFramework/Actor.h"
#include "LightObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API ALightObject : public AInteractObject
{
	GENERATED_BODY()
	
public:	
	ALightObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnEnter() override;
	virtual void OnInteract() override;
	virtual void OnExit() override;
};
