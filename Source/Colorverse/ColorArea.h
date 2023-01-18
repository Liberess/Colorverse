#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Components/BoxComponent.h"
#include "Engine/PostProcessVolume.h"
#include "ColorArea.generated.h"

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

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCol;

	UFUNCTION(BlueprintCallable)
	void SetEnabledPostProcess(bool Active);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ColorArea)
	bool IsLightness = false;
};
