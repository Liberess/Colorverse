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
	Maker UMETA(DisplayName = "Maker"),
	Statue UMETA(DisplayName = "Statue")
};

UENUM(BlueprintType)
enum class EItemCombineType : uint8
{
	Source UMETA(DisplayName = "Source"),
	Destination UMETA(DisplayName = "Destination"),
	Sacrifice UMETA(DisplayName = "Sacrifice")
};

UENUM(BlueprintType)
enum class ECombineColors : uint8
{
	Red UMETA(DisplayName = "Red"),
	Yellow UMETA(DisplayName = "Yellow"),
	Blue UMETA(DisplayName = "Blue")
};

UENUM(BlueprintType)
enum class ESacrificeType : uint8
{
	Unlock UMETA(DisplayName = "Unlock"),
	Recovery UMETA(DisplayName = "Recovery")
};

class COLORVERSE_API Enums
{
	
};
