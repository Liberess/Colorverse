#pragma once

#include "CoreMinimal.h"
#include "ContainerWidget.h"
#include "Statue.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "StatueWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UStatueWidget : public UContainerWidget
{
	GENERATED_BODY()

public:
	UStatueWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UCanvasPanel* UnlockCanvasPanel;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UCanvasPanel* RecoveryCanvasPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UUniformGridPanel* UnlockGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UUniformGridPanel* RecoveryGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UTextBlock* UnlockAmountTxt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	UProgressBar* RecoveryProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Statue, meta=(BindWidget))
	float RecoveryBarAmount;

	virtual void CreateContainer(int Slots) override;
	virtual void UpdateContainer(TArray<FItem> Items) override;

	UFUNCTION()
	void SetActiveCanvasPanel(bool IsUnlockPanel = true);
	
	UFUNCTION()
	void UpdateStatueUI(const AStatue* Statue);
};
