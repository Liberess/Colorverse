#include "ColorverseGameMode.h"
#include "ColorverseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AColorverseGameMode::AColorverseGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
