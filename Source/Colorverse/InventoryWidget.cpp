#include "InventoryWidget.h"
#include "InventoryManager.h"
#include "ItemSlotWidget.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Orange, text)

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptyImgObj(TEXT("/Game/Images/UI/EmptyImg"));
	if(EmptyImgObj.Object != nullptr)
		EmptyImg = EmptyImgObj.Object;
}

void UInventoryWidget::CreateInventory(int Slots)
{
	//ItemGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("ItemGridPanel")));
	//MakerGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("MakerGridPanel")));

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

void UInventoryWidget::UpdateInventory(TArray<FItem> Inventory)
{
	for (int i = 0; i < InventoryGridPanel->GetChildrenCount(); i++)
	{
		if (UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(InventoryGridPanel->GetChildAt(i)))
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Inventory.Num() ? Inventory[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

void UInventoryWidget::MoveItem(TArray<FItem>& SelectAry, TArray<FItem>& DropAry, bool IsMoveBetween)
{	
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr)

	SelectItem = SelectAry[SelectItemIndex];
	DropItem = DropAry[DropItemIndex];

	const static FItem EmptyItem = FItem();

	const bool IsSelectMaker = SelectAry.Num() <= 2;
	const bool IsSameCombineType = SelectItem.CombineType == DropItem.CombineType;

	//SelectItem이 Src고 Drop할 곳도 Src
	const bool IsSourceSwap = SelectItem.CombineType == EItemCombineType::Source && DropItemIndex == 0;
	//SelectItem이 Dest고 Drop할 곳도 Dest
	const bool IsDestinationSwap = SelectItem.CombineType == EItemCombineType::Destination && DropItemIndex == 1;
	
	if(IsMoveBetween)
	{
		if(DropItem.bIsValid)
		{
			if(SelectItem.Name.EqualTo(DropItem.Name))
			{
				DropAry[DropItemIndex] = DropItem;
				DropAry[DropItemIndex].Amount = SelectItem.Amount + DropItem.Amount;
				SelectAry[SelectItemIndex] = EmptyItem;
			}
			else if(IsSameCombineType)
			{
				DropAry[DropItemIndex] = SelectItem;
				SelectAry[SelectItemIndex] = DropItem;
				Print(1.0f, TEXT("1, 2"));
			}
		}
		else if(IsSelectMaker) //Maker -> Inventory
		{
			DropAry[DropItemIndex] = SelectItem;
			SelectAry[SelectItemIndex] = EmptyItem;
			Print(1.0f, TEXT("3"));
		}
		else if(IsSourceSwap || IsDestinationSwap)
		{
			DropAry[DropItemIndex] = SelectItem;
			SelectAry[SelectItemIndex] = EmptyItem;
			Print(1.0f, TEXT("4"));
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
					SelectAry[SelectItemIndex] = EmptyItem;
					Print(1.0f, TEXT("5"));
				}
				else
				{
					DropAry[DropItemIndex] = SelectItem;
					SelectAry[SelectItemIndex] = DropItem;
					Print(1.0f, TEXT("6"));
				}
			}
			else
			{
				DropAry[DropItemIndex] = SelectItem;
				SelectAry[SelectItemIndex] = EmptyItem;
				Print(1.0f, TEXT("7"));
			}
		}	
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
			//Source Item과 Destination Item은 전화할 수 없다.
			/*MoveItem(InvenMgr->MakerArray, InvenMgr->MakerArray, false);
			InvenMgr->UpdateInventory(true);*/
		}
		else
		{
			MoveItem(InvenMgr->MakerArray, InvenMgr->InventoryArray, true);
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateMaker();
		}
	}
	else
	{
		if(DropArrayMaker)
		{
			MoveItem(InvenMgr->InventoryArray,InvenMgr->MakerArray, true);
			
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateMaker();
		}
		else
		{
			MoveItem(InvenMgr->InventoryArray, InvenMgr->InventoryArray, false);
			InvenMgr->UpdateInventory();
		}
	}
}
