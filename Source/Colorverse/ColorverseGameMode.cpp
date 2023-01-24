#include "ColorverseGameMode.h"
#include "ColorManager.h"
#include "InventoryManager.h"
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

	UColorManager* ColorMgr = GetWorld()->GetSubsystem<UColorManager>();
	if(IsValid(ColorMgr))
		ColorMgr->InitializeManager();

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	if(IsValid(InvenMgr))
		InvenMgr->InitializeManager();
}
