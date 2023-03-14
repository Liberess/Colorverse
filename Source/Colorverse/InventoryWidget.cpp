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

void UInventoryWidget::CreateInventory(int Slots, bool IsMaker)
{
	//ItemGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("ItemGridPanel")));
	//MakerGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("MakerGridPanel")));

	UGridPanel* CurrentGrid = IsMaker ? MakerGridPanel : ItemGridPanel;
	
	FStringClassReference WidgetBPClassRef(TEXT("/Game/UI/BP_ItemSlot.BP_ItemSlot_C"));
	for(int i = 0; i < Slots - 1; i++)
	{
		if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UItemSlotWidget>())
		{
			UItemSlotWidget* Widget = Cast<UItemSlotWidget>(CreateWidget(GetWorld(), WidgetClass));
			Widget->bIsMaker = IsMaker;
			Widget->Index = i;
			int Row = i / GridColumnAmount;
			if(Row == 0)
				CurrentGrid->AddChildToGrid(Widget, Row, i);
			else
				CurrentGrid->AddChildToGrid(Widget, Row, i - (Row * GridColumnAmount));
		}
	}
}

void UInventoryWidget::UpdateInventory(TArray<FItem> Inventory, bool IsMaker)
{
	const UGridPanel* CurrentGrid = IsMaker ? MakerGridPanel : ItemGridPanel;

	for (int i = 0; i < CurrentGrid->GetChildrenCount(); i++)
	{
		UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(CurrentGrid->GetChildAt(i));
		if (ItemSlot)
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Inventory.Num() ? Inventory[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

void UInventoryWidget::MoveItem(TArray<FItem> SelectAry, TArray<FItem> DropAry, bool IsMoveBetween)
{	
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr)
	
	SelectItem = SelectAry[SelectItemIndex];
	DropItem = DropAry[DropItemIndex];
	
	if(IsMoveBetween)
	{
		if(DropItem.bIsValid)
		{
			if(SelectItem.Name.EqualTo(DropItem.Name))
			{
				DropAry[DropItemIndex] = DropItem;
				DropAry[DropItemIndex].Amount = SelectItem.Amount + DropItem.Amount;
				SelectAry[SelectItemIndex] = FItem();
			}
			else
			{
				DropAry[DropItemIndex] = SelectItem;
				SelectAry[SelectItemIndex] = DropItem;
			}
		}
		else
		{
			DropAry[DropItemIndex] = SelectItem;
			SelectAry[SelectItemIndex] = FItem();
		}
	}
	else
	{
		if(SelectItemIndex != DropItemIndex)
		{
			if(DropItem.bIsValid)
			{
				if(SelectItem.Name.EqualTo(DropItem.Name))
				{
					DropAry[DropItemIndex] = DropItem;
					DropAry[DropItemIndex].Amount = SelectItem.Amount + DropItem.Amount;
					SelectAry[SelectItemIndex] = FItem();
				}
				else
				{
					DropAry[DropItemIndex] = SelectItem;
					SelectAry[SelectItemIndex] = DropItem;
				}
			}
			else
			{
				DropAry[DropItemIndex] = SelectItem;
				SelectAry[SelectItemIndex] = FItem();
			}
		}	
	}
	
	if(SelectItemIndex != DropItemIndex)
	{
		const FItem SrcData = InvenMgr->InventoryArray[SelectItemIndex];
		const FItem DesData = InvenMgr->InventoryArray[DropItemIndex];
		
		if(DesData.bIsValid)
			InvenMgr->InventoryArray[SelectItemIndex] = DesData;
		else
			InvenMgr->InventoryArray[SelectItemIndex] = FItem();

		InvenMgr->InventoryArray[DropItemIndex] = SrcData;
	}
}

void UInventoryWidget::SetItemSlotArrays()
{
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr)
	
	if(SelectArrayMaker)
	{
		if(DropArrayMaker)
		{
			MoveItem(InvenMgr->MakerArray, InvenMgr->MakerArray, false);
			InvenMgr->UpdateInventory(true);
		}
		else
		{
			MoveItem(InvenMgr->MakerArray, InvenMgr->InventoryArray, true);
			InvenMgr->UpdateInventory(true);
			InvenMgr->UpdateInventory(false);
		}
	}
	else
	{
		if(DropArrayMaker)
		{
			MoveItem(InvenMgr->InventoryArray,InvenMgr->MakerArray, true);
			InvenMgr->UpdateInventory(true);
			InvenMgr->UpdateInventory(false);
		}
		else
		{
			MoveItem(InvenMgr->InventoryArray, InvenMgr->InventoryArray, false);
			InvenMgr->UpdateInventory(false);
		}
	}
}
