#include "InventoryWidget.h"
#include "ItemSlotWidget.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UInventoryWidget::CreateContainer(int Slots)
{
	for(int i = 0; i < InventoryGridPanel->GetChildrenCount(); i++)
	{
		if(UItemSlotWidget* Widget = Cast<UItemSlotWidget>(InventoryGridPanel->GetChildAt(i)))
		{
			Widget->bIsMaker = false;
			Widget->ItemLocation = EItemSlotLocationType::Inventory;
			Widget->Index = i;
		}
	}

	for(int i = 0; i < MakerGridPanel->GetChildrenCount(); i++)
	{
		if(UItemSlotWidget* Widget = Cast<UItemSlotWidget>(MakerGridPanel->GetChildAt(i)))
		{
			Widget->bIsMaker = true;
			Widget->ItemLocation = EItemSlotLocationType::Maker;
			Widget->Index = i;
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
			ItemSlot->ThumbnailImg->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

void UInventoryWidget::UpdateMakerContainer(TArray<FItem> Items)
{
	for (int i = 0; i < MakerGridPanel->GetChildrenCount(); i++)
	{
		if (UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(MakerGridPanel->GetChildAt(i)))
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Items.Num() ? Items[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailImg->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

void UInventoryWidget::SetCombineResultUI(const FItem& Item, bool IsAlreadyCombine)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Result"));
	ResultImg->SetBrushFromTexture(IsAlreadyCombine ? Item.IconImg : EmptyImg);
}
