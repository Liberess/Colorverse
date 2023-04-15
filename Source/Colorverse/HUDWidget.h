#pragma once

#include "CoreMinimal.h"
#include "PaintSlotWidget.h"
#include "IItem.h"
#include "ItemAcquiredWidget.h"
#include "ItemAcquiredWidgetPool.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "HUDWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Paint, meta=(BindWidget))
	UUniformGridPanel* PaintSlotGridPanel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Paint)
	TArray<UPaintSlotWidget*> PaintSlotWidgetArray;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item Acquired", meta=(BindWidget))
	UUniformGridPanel* ItemLogGridPanel;

	UPROPERTY(BlueprintReadOnly, Category = "Item Acquired")
	TSubclassOf<UItemAcquiredWidget> ItemAcquiredWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Item Acquired")
	UItemAcquiredWidgetPool* ItemLogPool;

public:
	UHUDWidget(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	void InitializedHUD();

	UFUNCTION(BlueprintCallable)
	void SetPaintBarPercent(int CombineColorNum, float Amount);

	UFUNCTION(BlueprintCallable)
	void AddItemLog(const FItem& ItemData);

	UFUNCTION(BlueprintCallable)
	void UpdateItemLog();
	
	UFUNCTION(BlueprintCallable)
	void ReleaseItemLogWidget(UItemAcquiredWidget* ItemLogWidget);
};
