#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "PaintedCollectObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API APaintedCollectObject : public AInteractObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsDrawing;
};
