#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Engine/PostProcessVolume.h"
#include "CustomPostProcessVolume.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API ACustomPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStageName StageName;
};
