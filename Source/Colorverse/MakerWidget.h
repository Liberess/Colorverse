#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "Blueprint/UserWidget.h"
#include "MakerWidget.generated.h"

UCLASS()
class COLORVERSE_API UMakerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMakerWidget(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int GridColumnAmount = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	UTexture2D* EmptyImg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory, meta=(BindWidget))
	UUniformGridPanel* MakerGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MakerShowAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MakerHideAnim;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CreateInventory(int Slots);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateMaker(TArray<FItem> Maker);

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
