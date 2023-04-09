#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "IInteractable.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InteractObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AInteractObject : public AActor, public IIInteractable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* BoxCol;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere,
		BlueprintGetter=GetInteractable,
		BlueprintSetter=SetInteractable,
		meta=(AllowPrivateAccess), Category=Interactable)
	bool IsInteractable = false;

	UFUNCTION()
	void SetEnabledInteractable(bool IsEnabled) { IsInteractable = IsEnabled; };

	UFUNCTION()
	void AddColorAreaEnabledAction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interactable)
	EStageName ParentStageName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interactable)
	FString InteractWidgetDisplayTxt;

	AInteractObject();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
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
