#include "ColorverseGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AColorverseGameMode::AColorverseGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_ColorverseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AColorverseGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ACustomPostProcessVolume::StaticClass(), Actors);
	for (auto Actor : Actors)
	{
		ACustomPostProcessVolume* PostVolume = Cast<ACustomPostProcessVolume>(Actor);
		PostVolumeMap.Add(PostVolume->StageName, PostVolume);
	}
}

void AColorverseGameMode::SetEnabledPostProcess(EStageName StageName, bool Active)
{
	if(PostVolumeMap.Num() > 0 && PostVolumeMap.Contains(StageName))
		PostVolumeMap[StageName]->bEnabled = Active;
}
