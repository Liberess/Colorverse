#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ColorverseGameMode.generated.h"

UCLASS(minimalapi)
class AColorverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AColorverseGameMode();

	virtual void BeginPlay() override;
};



