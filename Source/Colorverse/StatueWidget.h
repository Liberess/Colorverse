#pragma once

#include "CoreMinimal.h"
#include "ContainerWidget.h"
#include "StatueWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UStatueWidget : public UContainerWidget
{
	GENERATED_BODY()

public:
	UStatueWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UUniformGridPanel* UnlockGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UUniformGridPanel* RecoverGridPanel;

	virtual void CreateContainer(int Slots) override;
	virtual void UpdateContainer(TArray<FItem> Items) override;
};
