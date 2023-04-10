#include "ColorManager.h"
#include "ColorverseWorldSettings.h"
#include "LightObject.h"
#include "NavigationSystem.h"
#include "PaintedCollectObject.h"
#include "GameFramework/Character.h"
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

	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(this, APaintedCollectObject::StaticClass(), TempActors);
	for (auto TempActor : TempActors)
	{
		APaintedCollectObject* PaintObj = Cast<APaintedCollectObject>(TempActor);
		if(PaintObj->ParentStageName == EStageName::Stage_Tutorial)
		{
			PaintObj->SetInteractable(true);
			++TutorialRecoveryCapacity;
		}
	}
}

void UColorManager::SetLightAmount(EStageName StageName, int amount)
{
	if (LightAmountMap.Num() > 0 && LightAmountMap.Contains(StageName))
		LightAmountMap[StageName] += amount;
}

void UColorManager::SpawnTutorialLightObject()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	UClass* GeneratedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, TEXT("/Game/Blueprints/BP_LightObject.BP_LightObject_C")));

	auto Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto Location = Character->GetActorLocation();
	FNavLocation NavLocation;
	
	NavSystem->GetRandomReachablePointInRadius(Location, 100.0f, NavLocation);
	GetWorld()->SpawnActor<ALightObject>(GeneratedBP, NavLocation.Location, Character->GetActorRotation());
}
