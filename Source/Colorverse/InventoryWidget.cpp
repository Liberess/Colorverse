#include "InventoryWidget.h"
#include "ItemSlotWidget.h"

void UInventoryWidget::CreateInventory(int Slots)
{
	for(int i = 0; i < Slots - 1; i++)
	{
		UUserWidget* Widget = CreateWidget(GetWorld(), UItemSlotWidget::StaticClass());

		int Row = i / GridColumnAmount;
		if(Row == 0)
			ItemGridPanel->AddChildToGrid(Widget, Row, i);
		else
			ItemGridPanel->AddChildToGrid(Widget, Row, 0);
	}
}

void UInventoryWidget::UpdateInventory(TArray<FItem> Inventory)
{
	for(int i = 0; i < Inventory.Num(); i++)
	{
		//Inventory[i]
		UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(ItemGridPanel->GetChildAt(i));
		if(IsValid(ItemSlot))
		{
			ItemSlot->Index = i;
			if(IsValid(Inventory[i].IconImg))
			{
				ItemSlot->ItemBtn->WidgetStyle.Normal.SetResourceObject(Inventory[i].IconImg);
				ItemSlot->ItemBtn->WidgetStyle.Hovered.SetResourceObject(Inventory[i].IconImg);
			}
			else
			{
				ItemSlot->ItemBtn->WidgetStyle.Normal.SetResourceObject(nullptr);
				ItemSlot->ItemBtn->WidgetStyle.Hovered.SetResourceObject(nullptr);
			}
		}
	}
}
