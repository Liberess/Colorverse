#pragma once

#include "CoreMinimal.h"
#include "PaintSlotWidget.h"
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

public:
	UFUNCTION(BlueprintCallable)
	void InitializedHUD();

	UFUNCTION(BlueprintCallable)
	void SetPaintBarPercent(int CombineColorNum, float Amount);
};
