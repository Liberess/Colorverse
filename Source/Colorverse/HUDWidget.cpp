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

	if(UItemAcquiredWidget* ItemLogWidget = Cast<UItemAcquiredWidget>(ItemLogPool->GetOrCreateWidget(GetWorld(), ItemAcquiredWidgetClass)))
	{
		ItemLogWidget->SetVisibility(ESlateVisibility::Visible);
		ItemLogWidget->LogIndex = 0;
		ItemLogWidget->UpdateItemInformation(ItemData);
		ItemLogGridPanel->AddChildToUniformGrid(ItemLogWidget, 0, 0);
		UpdateItemLog();
	}

	/*const FSoftClassPath WidgetBPClassRef(TEXT("/Game/UI/BP_ItemAcquiredWidget.BP_ItemAcquiredWidget_C"));
	if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UItemAcquiredWidget>())
	{
		UpdateItemLog();
		UItemAcquiredWidget* ItemLogWidget = Cast<UItemAcquiredWidget>(CreateWidget(GetWorld(), WidgetClass));
		ItemLogWidget->LogIndex = 0;
		ItemLogWidget->UpdateItemInformation(ItemData);
		ItemLogGridPanel->AddChildToUniformGrid(ItemLogWidget, 0, 0);
		GetWorld()->GetTimerManager().SetTimer(ItemLogWidget->RemoveLogTimer, [this, ItemLogWidget]()
		{
			ItemLogWidget->SetVisibility(ESlateVisibility::Collapsed);
			ItemLogPool->ReleaseWidget(ItemLogWidget);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("auto release"));
		}, 3.0f, false);
	}*/
}

void UHUDWidget::UpdateItemLog()
{
	/*for(int i = ItemLogGridPanel->GetChildrenCount() - 1; i > 0; i--)
	{
		if(UItemAcquiredWidget* ItemWidget = Cast<UItemAcquiredWidget>(ItemLogGridPanel->GetChildAt(i)))
		{
			ItemWidget->UpdateItemLogIndex();
			if(UUniformGridSlot* ChildSlot = Cast<UUniformGridSlot>(ItemLogGridPanel->GetChildAt(i)->Slot))
				ChildSlot->SetRow(ItemWidget->LogIndex);
		}
	}*/
	
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
