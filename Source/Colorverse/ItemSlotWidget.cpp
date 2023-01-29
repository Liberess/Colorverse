#include "ItemSlotWidget.h"
#include "InventoryManager.h"

void UItemSlotWidget::OnClick_Implementation()
{
	ItemData = FItem();
	
	AmountTxt->SetText(FText::FromString(FString(TEXT(""))));
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr);
	InvenMgr->SetInventoryItem(Index);
}

void UItemSlotWidget::UpdateItemSlot(const FItem& Item)
{
	ItemData = Item;

	AmountTxt->SetText(FText::FromString(FString::FromInt(ItemData.Amount)));
}
