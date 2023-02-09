#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Interface.h"
#include "IItem.generated.h"

USTRUCT(BlueprintType, BlueprintType)
struct FItem : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY();

	FItem() : Id(-1), Amount(1), IconImg(), bIsValid(false) {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Amount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* IconImg;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsValid;
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
