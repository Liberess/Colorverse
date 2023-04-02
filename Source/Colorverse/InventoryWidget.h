#pragma once

#include "CoreMinimal.h"
#include "ContainerWidget.h"
#include "IItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UInventoryWidget : public UContainerWidget
{
	GENERATED_BODY()

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int GridColumnAmount = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory, meta=(BindWidget))
	UUniformGridPanel* InventoryGridPanel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InventoryShowAnim;

	virtual void CreateContainer(int Slots) override;
	virtual void UpdateContainer(TArray<FItem> Items) override;
};
