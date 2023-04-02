#include "ItemSlotWidget.h"
#include "InventoryManager.h"

void UItemSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if(ItemData.bIsValid)
	{
		NameTxt->SetText(ItemData.Name);
		NameBorder->SetVisibility(ESlateVisibility::Visible);
	}
}

void UItemSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	NameBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UItemSlotWidget::OnClick_Implementation()
{
	if(!ItemData.bIsValid || bIsMaker)
		return;

	UInventoryManager* InvenMgr = UUserWidget::GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->UseInventoryItem(ItemData);
}

void UItemSlotWidget::UpdateItemSlot(const FItem& Item)
{
	ItemData = Item;

	if(ItemData.bIsValid)
		AmountTxt->SetText(FText::FromString(FString::FromInt(ItemData.Amount)));
	else
		AmountTxt->SetText(FText::FromString(FString(TEXT(""))));
}
