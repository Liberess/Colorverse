#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStageName : uint8
{
	Stage_Red UMETA(DisplayName = "Stage_Red"),
	Stage_Orange UMETA(DisplayName = "Stage_Orange"),
	Stage_Yellow UMETA(DisplayName = "Stage_Yellow"),
	Stage_Blue UMETA(DisplayName = "Stage_Blue"),
	Stage_Tutorial UMETA(DisplayName = "Stage_Tutorial")
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
};

UENUM(BlueprintType)
enum class EItemCombineType : uint8
{
	Source UMETA(DisplayName = "Source"),
	Destination UMETA(DisplayName = "Destination")
};

UENUM(BlueprintType)
enum class ECombineColors : uint8
{
	Red UMETA(DisplayName = "Red"),
	Yellow UMETA(DisplayName = "Yellow"),
	Blue UMETA(DisplayName = "Blue"),
	Empty UMETA(DisplayName = "Empty")
};

UENUM(BlueprintType)
enum class EPaintComboColors : uint8
{
	Red UMETA(DisplayName = "Red"),
	Orange UMETA(DisplayName = "Orange"),
	Yellow UMETA(DisplayName = "Yellow"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue"),
	Purple UMETA(DisplayName = "Purple")
};

UENUM(BlueprintType)
enum class EPuzzleTag : uint8
{
	Puzzle_Red UMETA(DisplayName = "Puzzle_Red"),
	Puzzle_Yellow UMETA(DisplayName = "Puzzle_Yellow"),
	Puzzle_Blue UMETA(DisplayName = "Puzzle_Blue"),
	Puzzle_Last UMETA(DisplayName = "Puzzle_Last")
};

class COLORVERSE_API Enums
{
	
};
