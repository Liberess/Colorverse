#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IItem.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Amount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* IconImg;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsValid = false;
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
