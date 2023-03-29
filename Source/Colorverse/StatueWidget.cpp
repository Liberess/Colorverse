#include "StatueWidget.h"
#include "ItemSlotWidget.h"

UStatueWidget::UStatueWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UStatueWidget::CreateContainer(int Slots)
{
	for(int i = 0; i < UnlockGridPanel->GetChildrenCount(); i++)
	{
		if(UItemSlotWidget* Widget = Cast<UItemSlotWidget>(UnlockGridPanel->GetChildAt(i)))
		{
			Widget->bIsMaker = true;
			Widget->Index = i;
		}
	}
}

void UStatueWidget::UpdateContainer(TArray<FItem> Items)
{
	for (int i = 0; i < UnlockGridPanel->GetChildrenCount(); i++)
	{
		if (UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(UnlockGridPanel->GetChildAt(i)))
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Items.Num() ? Items[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

