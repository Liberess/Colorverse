#pragma once

#include "CoreMinimal.h"
#include "ColorArea.h"
#include "Enums.h"
#include "ColorverseGameMode.h"
#include "Subsystems/WorldSubsystem.h"
#include "ColorManager.generated.h"

UCLASS()
class COLORVERSE_API UColorManager : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	TMap<EStageName, int> LightAmountMap;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess))
	TMap<EStageName, AColorArea*> ColorAreaMap;

	AColorverseGameMode* GameMode;
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();
	
	UFUNCTION(BlueprintGetter)
	int GetLightAmount(EStageName StageName) { return LightAmountMap[StageName]; }
	
	UFUNCTION(BlueprintSetter)
	void SetLightAmount(EStageName StageName, int amount);
};
