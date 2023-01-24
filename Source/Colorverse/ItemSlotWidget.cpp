#include "ItemSlotWidget.h"
#include "InventoryManager.h"

void UItemSlotWidget::OnClick_Implementation()
{
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr);
	InvenMgr->SetInventoryItem(Index);
}

