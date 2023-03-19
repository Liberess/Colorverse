#include "HUDWidget.h"

void UHUDWidget::InitializedHUD()
{
	for(int i = 0; i < PaintSlotGridPanel->GetChildrenCount(); i++)
	{
		if(UPaintSlotWidget* Widget = Cast<UPaintSlotWidget>(PaintSlotGridPanel->GetChildAt(i)))
		{
			Widget->SetPaintColor(static_cast<ECombineColors>(i));
			Widget->SetInputKeyText(FString::FromInt(i+1));
			Widget->SetPaintBarPercent(0.0f);
			PaintSlotWidgetArray.Add(Widget);
		}
	}
}

void UHUDWidget::SetPaintBarPercent(int CombineColorNum, float Amount)
{
	PaintSlotWidgetArray[CombineColorNum]->SetPaintBarPercent(Amount);
}
