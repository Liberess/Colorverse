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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory)
	UGridPanel* ItemGridPanel;
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CreateInventory(int Slots);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateInventory(TArray<FItem> Inventory);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	int SelectItemIndex = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Inventory)
	int DropItemIndex = 0;
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void MoveItem();
};
