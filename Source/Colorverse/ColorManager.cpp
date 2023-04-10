#include "ColorManager.h"
#include "ColorverseWorldSettings.h"
#include "Kismet/GameplayStatics.h"

bool UColorManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
		return false;

	const UWorld* WorldOuter = Cast<UWorld>(Outer);
	if (IsValid(WorldOuter))
	{
		AColorverseWorldSettings* WorldSettings = Cast<AColorverseWorldSettings>(WorldOuter->GetWorldSettings());
		if (IsValid(WorldSettings))
			return WorldSettings->bUseColorManager;
	}

	return false;
}

void UColorManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LightAmountMap.Add(EStageName::Stage_Red, 0);
	LightAmountMap.Add(EStageName::Stage_Orange, 0);
	LightAmountMap.Add(EStageName::Stage_Yellow, 0);
	LightAmountMap.Add(EStageName::Stage_Blue, 0);
}

void UColorManager::InitializeManager()
{
	GameMode = Cast<AColorverseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, AColorArea::StaticClass(), Actors);
	for (auto Actor : Actors)
	{
		AColorArea* ColorArea = Cast<AColorArea>(Actor);
		ColorAreaMap.Add(ColorArea->StageName, ColorArea);
	}
}

void UColorManager::SetLightAmount(EStageName StageName, int amount)
{
	if (LightAmountMap.Num() > 0 && LightAmountMap.Contains(StageName))
		LightAmountMap[StageName] += amount;
}
