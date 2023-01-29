#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ItemSlotWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* ItemBtn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* AmountTxt;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* NameTxt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* NameBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FItem ItemData;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnClick();

	UFUNCTION(BlueprintCallable)
	void UpdateItemSlot(const FItem& Item);
};
