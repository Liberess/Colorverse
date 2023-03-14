#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStageName : uint8
{
	Stage_1 UMETA(DisplayName = "Stage_1"),
	Stage_2 UMETA(DisplayName = "Stage_2"),
	Stage_3 UMETA(DisplayName = "Stage_3")
};

UENUM(BlueprintType)
enum class ECollectType : uint8
{
	Tree UMETA(DisplayName = "Tree"),
	Ground UMETA(DisplayName = "Ground"),
	Ore UMETA(DisplayName = "Ore")
};

UENUM(BlueprintType)
enum class EItemSlotLocationType : uint8
{
	Inventory UMETA(DisplayName = "Inventory"),
	Maker UMETA(DisplayName = "Maker")
};

class COLORVERSE_API Enums
{
	
};
