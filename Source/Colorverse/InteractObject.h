#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AInteractObject : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnEnter() override;
	
	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnExit() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interactable)
	FString InteractWidgetDisplayTxt;
};
