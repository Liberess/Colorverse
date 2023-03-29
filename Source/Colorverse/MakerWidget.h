#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "MakerWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UMakerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMakerWidget(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Maker)
	UTexture2D* EmptyImg;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Maker, meta=(BindWidget))
	UUniformGridPanel* MakerGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MakerShowAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* MakerHideAnim;

	UFUNCTION(BlueprintCallable, Category=Maker)
	void CreateMaker(int Slots);
	
	UFUNCTION(BlueprintCallable, Category=Maker)
	void UpdateMaker(TArray<FItem> Maker);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	int SelectItemIndex = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	int DropItemIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	FItem SelectItem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	FItem DropItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	bool SelectArrayMaker;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Maker)
	bool DropArrayMaker;
	
	UFUNCTION(BlueprintCallable, Category=Maker)
	void MoveItem(TArray<FItem>& SelectAry, TArray<FItem>& DropAry, bool IsMoveBetween);

	UFUNCTION(BlueprintCallable, Category=Maker)
	void SetItemSlotArrays();
};
