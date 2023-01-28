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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GridColumnAmount = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* EmptyImg;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly/*, meta=(BindWidget)*/)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGridPanel* ItemGridPanel;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CreateInventory(int Slots);
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateInventory(TArray<FItem> Inventory);
};
