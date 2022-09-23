// Copyright Epic Games, Inc. All Rights Reserved.

#include "ColorverseGameMode.h"
#include "ColorverseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AColorverseGameMode::AColorverseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
