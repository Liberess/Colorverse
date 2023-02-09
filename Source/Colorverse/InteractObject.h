#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AInteractObject : public AActor, public IIInteractable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetInteractable,
		BlueprintSetter=SetInteractable,
		meta=(AllowPrivateAccess), Category=Interactable)
	bool IsInteractable = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interactable)
	FString InteractWidgetDisplayTxt;

	AInteractObject();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnEnter() override;

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnInteract() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Interactable)
	void Interact();
	virtual void Interact_Implementation();

	UFUNCTION(BlueprintCallable, Category=Interactable)
	virtual void OnExit() override;

	UFUNCTION(BlueprintGetter)
	bool GetInteractable() const { return IsInteractable; }

	UFUNCTION(BlueprintSetter)
	void SetInteractable(bool Enabled) { IsInteractable = Enabled; }
};
