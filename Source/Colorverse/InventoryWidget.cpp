#include "InventoryWidget.h"
#include "ItemSlotWidget.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Orange, text)

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UInventoryWidget::CreateContainer(int Slots)
{
	const FSoftClassPath WidgetBPClassRef(TEXT("/Game/UI/BP_ItemSlot.BP_ItemSlot_C"));
	for(int i = 0; i < Slots - 1; i++)
	{
		if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UItemSlotWidget>())
		{
			UItemSlotWidget* Widget = Cast<UItemSlotWidget>(CreateWidget(GetWorld(), WidgetClass));
			Widget->bIsMaker = false;
			Widget->Index = i;
			int Row = i / GridColumnAmount;
			if(Row == 0)
				InventoryGridPanel->AddChildToUniformGrid(Widget, Row, i);
			else
				InventoryGridPanel->AddChildToUniformGrid(Widget, Row, i - (Row * GridColumnAmount));
		}
	}
}

void UInventoryWidget::UpdateContainer(TArray<FItem> Items)
{
	for (int i = 0; i < InventoryGridPanel->GetChildrenCount(); i++)
	{
		if (UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(InventoryGridPanel->GetChildAt(i)))
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Items.Num() ? Items[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}
