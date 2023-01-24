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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GridColumnAmount = 6;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UGridPanel* ItemGridPanel;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CreateInventory(int Slots);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateInventory(TArray<FItem> Inventory);
};
