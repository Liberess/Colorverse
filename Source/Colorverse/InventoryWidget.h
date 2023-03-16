#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "InventoryWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int GridColumnAmount = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	UTexture2D* EmptyImg;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly/*, meta=(BindWidget)*/)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory, meta=(BindWidget))
	UGridPanel* ItemGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory, meta=(BindWidget))
	UGridPanel* MakerGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InventoryShowAnim;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CreateInventory(int Slots, bool IsMaker);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateInventory(TArray<FItem> Inventory, bool IsMaker);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	int SelectItemIndex = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	int DropItemIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	FItem SelectItem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	FItem DropItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	bool SelectArrayMaker;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	bool DropArrayMaker;
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void MoveItem(TArray<FItem>& SelectAry, TArray<FItem>& DropAry, bool IsMoveBetween);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void SetItemSlotArrays();
};
