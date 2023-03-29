#include "MakerWidget.h"
#include "ItemSlotWidget.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Blue, text)

UMakerWidget::UMakerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptyImgObj(TEXT("/Game/Images/UI/EmptyImg"));
	if(EmptyImgObj.Object != nullptr)
		EmptyImg = EmptyImgObj.Object;
}

void UMakerWidget::CreateInventory(int Slots)
{
	for(int i = 0; i < MakerGridPanel->GetChildrenCount(); i++)
	{
		if(UItemSlotWidget* Widget = Cast<UItemSlotWidget>(MakerGridPanel->GetChildAt(i)))
		{
			Widget->bIsMaker = true;
			Widget->Index = i;
		}
	}
}

void UMakerWidget::UpdateMaker(TArray<FItem> Maker)
{
	for (int i = 0; i < MakerGridPanel->GetChildrenCount(); i++)
	{
		if (UItemSlotWidget* ItemSlot = Cast<UItemSlotWidget>(MakerGridPanel->GetChildAt(i)))
		{
			ItemSlot->Index = i;
			const FItem& Item = i < Maker.Num() ? Maker[i] : FItem();
			ItemSlot->UpdateItemSlot(Item);
			ItemSlot->ThumbnailBorder->SetBrushFromTexture(Item.bIsValid ? Item.IconImg : EmptyImg);
		}
	}
}

void UMakerWidget::MoveItem(TArray<FItem>& SelectAry, TArray<FItem>& DropAry, bool IsMoveBetween)
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

void UMakerWidget::SetItemSlotArrays()
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
