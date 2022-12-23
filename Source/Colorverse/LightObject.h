#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "LightObject.generated.h"

UCLASS()
class COLORVERSE_API ALightObject : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	ALightObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnEnter() override;
	
	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnInteract() override;
	
	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnExit() override;
};
