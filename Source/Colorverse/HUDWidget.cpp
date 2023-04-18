#include "HUDWidget.h"
#include "Components/UniformGridSlot.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemLogPool = CreateDefaultSubobject<UItemAcquiredWidgetPool>(TEXT("ItemLogWidgetPool"));
}

void UHUDWidget::InitializedHUD()
{
	const FSoftClassPath WidgetBPClassRef(TEXT("/Game/UI/BP_ItemAcquiredWidget.BP_ItemAcquiredWidget_C"));
	if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UItemAcquiredWidget>())
		ItemAcquiredWidgetClass = WidgetClass;
	
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

void UHUDWidget::AddItemLog(const FItem& ItemData)
{
	if(!ItemData.bIsValid || !ItemAcquiredWidgetClass)
		return;

	for(auto& Child : ItemLogGridPanel->GetAllChildren())
	{
		if(UItemAcquiredWidget* ItemWidget = Cast<UItemAcquiredWidget>(Child))
		{
			if(ItemData.Name.EqualTo(ItemWidget->ItemData.Name))
			{
				ItemWidget->LogIndex = 0;
				ItemWidget->ItemData.Amount += ItemData.Amount;
				if(UUniformGridSlot* ChildSlot = Cast<UUniformGridSlot>(Child->Slot))
					ChildSlot->SetRow(ItemWidget->LogIndex);
				ItemWidget->UpdateItemInformation();
				ItemWidget->SetupItemLogTimer();
				return;
			}
		}
	}

	if(UItemAcquiredWidget* ItemLogWidget = Cast<UItemAcquiredWidget>(ItemLogPool->GetOrCreateWidget(GetWorld(), ItemAcquiredWidgetClass)))
	{
		ItemLogWidget->SetVisibility(ESlateVisibility::Visible);
		ItemLogWidget->LogIndex = 0;
		ItemLogWidget->bIsViewComplete = false;
		ItemLogWidget->SetupItemWidget(ItemData);
		ItemLogGridPanel->AddChildToUniformGrid(ItemLogWidget, 0, 0);
		UpdateItemLog();
	}
}

void UHUDWidget::UpdateItemLog()
{
	for(auto& Child : ItemLogGridPanel->GetAllChildren())
	{
		if(UItemAcquiredWidget* ItemWidget = Cast<UItemAcquiredWidget>(Child))
		{
			ItemWidget->UpdateItemLogIndex();
			if(UUniformGridSlot* ChildSlot = Cast<UUniformGridSlot>(Child->Slot))
				ChildSlot->SetRow(ItemWidget->LogIndex);
		}
	}
}

void UHUDWidget::ReleaseItemLogWidget(UItemAcquiredWidget* ItemLogWidget)
{
	ItemLogPool->ReleaseWidget(ItemLogWidget);
}
