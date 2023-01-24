#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ItemSlotWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* ItemBtn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Index;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnClick();
};
