#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/NoExportTypes.h"
#include "ItemAcquiredWidgetPool.generated.h"

USTRUCT(BlueprintType)
struct FWidgetData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UUserWidget*> WidgetArray;
};

UCLASS()
class COLORVERSE_API UItemAcquiredWidgetPool : public UObject
{
	GENERATED_BODY()

public:
	UItemAcquiredWidgetPool();

	UFUNCTION(BlueprintCallable, Category = "Item Acquired Widget Pool")
	UUserWidget* GetOrCreateWidget(UObject* WorldContextObject, TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Item Acquired Widget Pool")
	void ReleaseWidget(UUserWidget* Widget);

private:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, FWidgetData> PoolMap;
};
