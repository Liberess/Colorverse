#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DialogueWidget.generated.h"

UCLASS(BlueprintType)
class COLORVERSE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NPCNameTxt;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DialogueTxt;

	UFUNCTION(BlueprintCallable)
	void SetDialogueText(FText Name, FText Dialogue);
};
