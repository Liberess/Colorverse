#include "ContainerWidget.h"
#include "InventoryManager.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Yellow, text);

UContainerWidget::UContainerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmptyImgObj(TEXT("/Game/Images/UI/EmptyImg"));
	if(EmptyImgObj.Object != nullptr)
		EmptyImg = EmptyImgObj.Object;
}

void UContainerWidget::MoveItem(TArray<FItem>& SelectAry, TArray<FItem>& DropAry, bool IsMoveBetween)
{
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr)

	SelectItem = SelectAry[SelectItemIndex];
	DropItem = DropAry[DropItemIndex];

	const static FItem EmptyItem = FItem();

	if(SelectLocation == EItemSlotLocationType::Statue || DropLocation == EItemSlotLocationType::Statue)
	{
		if(IsMoveBetween)
		{
			if(DropItem.bIsValid)
			{
				if(SelectItem.Name.EqualTo(DropItem.Name))
				{
					DropAry[DropItemIndex] = DropItem;
					DropAry[DropItemIndex].Amount = SelectItem.Amount + DropItem.Amount;
					SelectAry[SelectItemIndex] = EmptyItem;
					Print(1.0f, TEXT("10"));
				}
				else if(SelectItem.CombineType == DropItem.CombineType &&
					SelectItem.CombineType == EItemCombineType::Sacrifice)
				{
					DropAry[DropItemIndex] = SelectItem;
					SelectAry[SelectItemIndex] = DropItem;
					Print(1.0f, TEXT("11"));
				}
			}
			else if(SelectItem.CombineType == EItemCombineType::Sacrifice) //Statue -> Inventory
			{
				DropAry[DropItemIndex] = SelectItem;
				SelectAry[SelectItemIndex] = EmptyItem;
				Print(1.0f, TEXT("12"));
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
						Print(1.0f, TEXT("13"));
					}
					else
					{
						DropAry[DropItemIndex] = SelectItem;
						SelectAry[SelectItemIndex] = DropItem;
						Print(1.0f, TEXT("14"));
					}
				}
				else
				{
					DropAry[DropItemIndex] = SelectItem;
					SelectAry[SelectItemIndex] = EmptyItem;
					Print(1.0f, TEXT("15"));
				}
			}
		}
	}
	else
	{
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
					Print(1.0f, TEXT("1"));
				}
				else if(IsSameCombineType)
				{
					DropAry[DropItemIndex] = SelectItem;
					SelectAry[SelectItemIndex] = DropItem;
					Print(1.0f, TEXT("2"));
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
}

void UContainerWidget::SetItemSlotArrays()
{
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr)

	switch (SelectLocation)
	{
	case EItemSlotLocationType::Inventory:
		if(DropLocation == EItemSlotLocationType::Maker)
		{
			MoveItem(InvenMgr->InventoryArray,InvenMgr->MakerArray, true);
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateMaker();
		}
		else if(DropLocation == EItemSlotLocationType::Statue)
		{
			MoveItem(InvenMgr->InventoryArray,InvenMgr->StatueArray, true);
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateStatue();
		}
		else
		{
			MoveItem(InvenMgr->InventoryArray, InvenMgr->InventoryArray, false);
			InvenMgr->UpdateInventory();
		}
		break;

	case EItemSlotLocationType::Maker:
		if(DropLocation == EItemSlotLocationType::Inventory)
		{
			MoveItem(InvenMgr->MakerArray, InvenMgr->InventoryArray, true);
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateMaker();
		}
		break;

	case EItemSlotLocationType::Statue:
		if(DropLocation == EItemSlotLocationType::Inventory)
		{
			MoveItem(InvenMgr->StatueArray, InvenMgr->InventoryArray, true);
			InvenMgr->UpdateInventory();
			InvenMgr->UpdateStatue();
		}
		else if(DropLocation == EItemSlotLocationType::Statue)
		{
			MoveItem(InvenMgr->StatueArray, InvenMgr->StatueArray, false);
			InvenMgr->UpdateStatue();
		}
		break;
	}
}
