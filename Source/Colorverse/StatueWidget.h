#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatueWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UStatueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UStatueWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Statue)
	UTexture2D* EmptyImg;
	
	UFUNCTION(BlueprintCallable, Category=Statue)
	void CreateStatue();
};
