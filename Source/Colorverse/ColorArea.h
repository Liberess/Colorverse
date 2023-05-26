#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Components/BoxComponent.h"
#include "Engine/PostProcessVolume.h"
#include "ColorArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetEnabledStageInteract, bool, IsEnabled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisabledStageInteract);

UCLASS(Blueprintable, BlueprintType)
class COLORVERSE_API AColorArea : public AInteractObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	AColorArea();
	
	virtual void OnEnter_Implementation() override;
	virtual void OnInteract_Implementation() override;
	virtual void OnExit_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ColorArea)
	EPuzzleTag PuzzleTag = EPuzzleTag::Puzzle_Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ColorArea|Effect")
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
