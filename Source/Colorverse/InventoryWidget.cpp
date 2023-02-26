#include "InventoryWidget.h"
#include "InventoryManager.h"
#include "ItemSlotWidget.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptyImgObj(TEXT("/Game/Images/UI/EmptyImg"));
	if(EmptyImgObj.Object != nullptr)
		EmptyImg = EmptyImgObj.Object;
}

void UInventoryWidget::CreateInventory(int Slots)
{
	ItemGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("GridPanel")));
	MakerGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("MakerGridPanel")));
	
	FStringClassReference WidgetBPClassRef(TEXT("/Game/UI/BP_ItemSlot.BP_ItemSlot_C"));
	for(int i = 0; i < Slots - 1; i++)
	{
		if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UItemSlotWidget>())
		{
			UUserWidget* Widget = Cast<UItemSlotWidget>(CreateWidget(GetWorld(), WidgetClass));
			int Row = i / GridColumnAmount;
			if(Row == 0)
				ItemGridPanel->AddChildToGrid(Widget, Row, i);
			else
				ItemGridPanel->AddChildToGrid(Widget, Row, i - (Row * GridColumnAmount));
		}
	}
}

void UInventoryWidget::UpdateInventory(TArray<FItem> Inventory)
{
	for(int i = 0; i < Inventory.Num(); i++)
	{
		UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(ItemGridPanel->GetChildAt(i));
		if(IsValid(ItemSlot))
		{
			ItemSlot->Index = i;
			//if(IsValid(Inventory[i].IconImg))
			if(Inventory[i].bIsValid)
			{
				//ItemSlot->ItemBtn->SetVisibility(ESlateVisibility::Visible);
				ItemSlot->UpdateItemSlot(Inventory[i]);
				ItemSlot->ThumbnailBorder->SetBrushFromTexture(Inventory[i].IconImg);
				/*ItemSlot->ItemBtn->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(Inventory[i].IconImg));
				ItemSlot->ItemBtn->WidgetStyle.Hovered.SetResourceObject(Cast<UObject>(Inventory[i].IconImg));
				ItemSlot->ItemBtn->WidgetStyle.Normal.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
				ItemSlot->ItemBtn->WidgetStyle.Hovered.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);*/
			}
			else
			{
				//ItemSlot->ItemBtn->SetVisibility(ESlateVisibility::Hidden);
				ItemSlot->UpdateItemSlot(FItem());
				ItemSlot->ThumbnailBorder->SetBrushFromTexture(EmptyImg);
				/*ItemSlot->ItemBtn->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(EmptyImg));
				ItemSlot->ItemBtn->WidgetStyle.Hovered.SetResourceObject(Cast<UObject>(EmptyImg));
				ItemSlot->ItemBtn->WidgetStyle.Normal.TintColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.8f);
				ItemSlot->ItemBtn->WidgetStyle.Hovered.TintColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.8f);*/
			}
		}
	}
}

void UInventoryWidget::MoveItem()
{
	if(SelectItemIndex != DropItemIndex)
	{
		UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
		check(InvenMgr);

		FItem SrcData = InvenMgr->GetInventoryItem(SelectItemIndex);
		FItem DesData = InvenMgr->GetInventoryItem(DropItemIndex);
		
		if(DesData.bIsValid)
			InvenMgr->SetInventoryItem(SelectItemIndex, DesData);
		else
			InvenMgr->SetInventoryItem(SelectItemIndex);

		InvenMgr->SetInventoryItem(DropItemIndex, SrcData);
	}
}
