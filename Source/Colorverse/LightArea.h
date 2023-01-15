#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LightArea.generated.h"

UCLASS()
class COLORVERSE_API ALightArea : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	ALightArea();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
