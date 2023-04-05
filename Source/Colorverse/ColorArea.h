#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Components/BoxComponent.h"
#include "Engine/PostProcessVolume.h"
#include "ColorArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetEnabledStageInteract, bool, IsEnabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisabledStageInteract);

UCLASS()
class COLORVERSE_API AColorArea : public AInteractObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	AColorArea();
	virtual void OnEnter() override;
	virtual void OnInteract() override;
	virtual void OnExit() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interactable)
	EStageName StageName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Effect)
	APostProcessVolume* PostVolume;

	UFUNCTION(BlueprintCallable)
	void SetEnabledPostProcess(bool Active);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ColorArea)
	bool IsLightness = false;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category=ColorArea)
	FOnSetEnabledStageInteract OnSetEnabledStageInteract;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category=ColorArea)
	FOnDisabledStageInteract OnDisabledStageInteract;
};
