#include "ItemAcquiredWidget.h"
#include "HUDWidget.h"

void UItemAcquiredWidget::UpdateItemInformation(const FItem& ItemData)
{
	ItemImg->SetBrushFromTexture(ItemData.IconImg);
	ItemNameTxt->SetText(ItemData.Name);
	ItemAmountTxt->SetText(FText::FromString("x" + FString::FromInt(ItemData.Amount)));
	PlayAnimation(ShowAnim);

	GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
	GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
	{
		StopAnimation(ShowAnim);
		PlayAnimation(HideAnim);

		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, FTimerDelegate::CreateLambda([&]()
		{
			SetVisibility(ESlateVisibility::Collapsed);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("auto release"));
		}), 1.0f, false);
	}, 2.0f, false);
}

void UItemAcquiredWidget::UpdateItemLogIndex()
{
	++LogIndex;
	if(LogIndex >= 4)
	{
		StopAnimation(ShowAnim);
		PlayAnimation(HideAnim);
		GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("over 4"));
			SetVisibility(ESlateVisibility::Collapsed);
			//ItemLogPool->ReleaseWidget(ItemWidget);
		}, 1.0f, false);
	}
	else if(LogIndex >= 3)
	{
		StopAnimation(ShowAnim);
		GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
		{
			StopAnimation(ShowAnim);
			PlayAnimation(HideAnim);

			/*GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, FTimerDelegate::CreateLambda([&]()
			{
				ReleaseItemLogWidget();
			}), 1.0f, false);*/

			GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer,
				FTimerDelegate::CreateUObject(this, &UItemAcquiredWidget::ReleaseItemLogWidget), 1.0f, false);
		}, 1.0f, false);
	}
}

void UItemAcquiredWidget::ReleaseItemLogWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
	const FSoftClassPath WidgetClassRef(TEXT("/Script/HUDWidget.HUDWidget_C"));
	if(UClass* WidgetClass = WidgetClassRef.TryLoadClass<UItemAcquiredWidget>())
	{
		if(UHUDWidget* HUDWidget = Cast<UHUDWidget>(WidgetClass))
			HUDWidget->ReleaseItemLogWidget(this);
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("release"));
}
