#pragma once

#include "CoreMinimal.h"
#include "CustomPostProcessVolume.h"
#include "GameFramework/GameModeBase.h"
#include "ColorverseGameMode.generated.h"

UCLASS()
class AColorverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TMap<EStageName, ACustomPostProcessVolume*> PostVolumeMap;

public:
	AColorverseGameMode();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetEnabledPostProcess(EStageName StageName, bool Active);
};



