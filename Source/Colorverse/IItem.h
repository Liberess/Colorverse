#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Engine/DataTable.h"
#include "UObject/Interface.h"
#include "IItem.generated.h"

USTRUCT(BlueprintType, BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	
public:
	FItem() : Id(-1), CombineType(EItemCombineType::Source), Amount(1), RecoveryAmount(0.0f), IconImg(), bIsValid(false) {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemCombineType CombineType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Amount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float RecoveryAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* IconImg;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsValid;
};

USTRUCT(BlueprintType, BlueprintType)
struct FCombine : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combine")
	FText CombineName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combine")
	FText ResultItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combine")
	ECombineColors CombineColor;
};

UINTERFACE(MinimalAPI)
class UIItem : public UInterface
{
	GENERATED_BODY()
};

class COLORVERSE_API IIItem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	void OnUse();
};
