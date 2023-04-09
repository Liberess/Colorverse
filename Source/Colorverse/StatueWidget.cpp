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
			Widget->ItemLocation = EItemSlotLocationType::StatueUnlock;
			Widget->Index = i;
			UnlockItemSlots.Add(Widget);
		}
	}

	for(int i = 0; i < RecoveryGridPanel->GetChildrenCount(); i++)
	{
		if(UItemSlotWidget* Widget = Cast<UItemSlotWidget>(RecoveryGridPanel->GetChildAt(i)))
		{
			Widget->ItemLocation = EItemSlotLocationType::StatueRecovery;
			Widget->Index = i;
			RecoveryItemSlots.Add(Widget);
		}
	}
}

void UStatueWidget::UpdateContainer(TArray<FItem> Items)
{
	for (int i = 0; i < UnlockItemSlots.Num(); i++)
	{
		UnlockItemSlots[i]->Index = i;
		const FItem& Item = i < Items.Num() ? Items[i] : FItem();
		UnlockItemSlots[i]->UpdateItemSlot(Item);
		UnlockItemSlots[i]->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
	}

	for (int i = 0; i < RecoveryItemSlots.Num(); i++)
	{
		RecoveryItemSlots[i]->Index = i;
		const FItem& Item = i < Items.Num() ? Items[i] : FItem();
		RecoveryItemSlots[i]->UpdateItemSlot(Item);
		RecoveryItemSlots[i]->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
	}
}

/**
 * @brief 
 * @param IsUnlockPanel 이 true라면 UnlockCanvasPanel을 Visible로
 */
void UStatueWidget::SetActiveCanvasPanel(bool IsUnlockPanel)
{
	if(IsUnlockPanel)
	{
		UnlockCanvasPanel->SetVisibility(ESlateVisibility::Visible);
		RecoveryCanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UnlockCanvasPanel->SetVisibility(ESlateVisibility::Hidden);
		RecoveryCanvasPanel->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStatueWidget::UpdateStatueUI(const AStatue* Statue)
{
	// 성소가 해금된 상태라면, 색을 되찾는 UI로 세팅
	if(Statue->bIsUnlockComplete)
	{
		RecoveryBarAmount = Statue->RecoveryAmount;
		MaxRecoveryBarAmount = Statue->RecoveryCapacity;

		WorldRecoveryBarAmount = Statue->WorldRecoveryAmount;
		MaxWorldRecoveryBarAmount = Statue->WorldRecoveryCapacity;
	}
	else
	{
		FString UnlockTxt = FString::Printf(TEXT("%d/%d"), Statue->UnlockCount, Statue->UnlockCapacity);
		UnlockAmountTxt->SetText(FText::FromString(UnlockTxt));
	}
}

